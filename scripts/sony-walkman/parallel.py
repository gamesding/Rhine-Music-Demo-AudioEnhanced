"""Bounded multi-core pipeline. Each Sony effect owns one continuous ARM state."""
import multiprocessing as mp
import queue, threading

def stage_worker(inbox, outbox, settings):
    parent = mp.parent_process()
    def send(value):
        while parent is None or parent.is_alive():
            try: outbox.put(value,timeout=.5); return
            except queue.Full: continue
        raise SystemExit()
    try:
        from effects import create_chain, feed_chain, finish_chain
        import arm_runtime as arm
        chain, _ = create_chain(*settings)
        while True:
            try: content = inbox.get(timeout=.5)
            except queue.Empty:
                if parent is not None and not parent.is_alive(): return
                continue
            if content is None:
                tail = finish_chain(chain)
                if tail: send(tail)
                send({'imports': sorted(arm.called)})
                send(None)
                return
            if isinstance(content, dict):
                send(content)
                if 'error' in content:
                    send(None)
                    return
                continue
            output = feed_chain(chain, content)
            if output: send(output)
    except Exception as error:
        send({'error': str(error)})
        send(None)

class ParallelChain:
    def __init__(self, decoder, rate, dsee, dc, vinyl, workers=3):
        self.decoder = decoder; self.frames = 0; self.closed = False; self.imports = set()
        context = mp.get_context('spawn')
        stages = []
        if dsee: stages.append((rate, True, 0, 0)); rate *= 4
        if dc: stages.append((rate, False, dc, 0))
        if vinyl: stages.append((rate, False, 0, vinyl))
        if len(stages) > workers:
            # On a two-core CPU, keep AI+phase in one ordered stage and vinyl in the other.
            first, second = stages[:2]
            stages[:2] = [(first[0],first[1],second[2],second[3])]
        self.queues = [context.Queue(maxsize=2) for _ in range(len(stages)+1)]
        self.processes = [context.Process(target=stage_worker,args=(self.queues[i],self.queues[i+1],settings),daemon=True) for i,settings in enumerate(stages)]
        for process in self.processes: process.start()
        self.thread = threading.Thread(target=self.feed,daemon=True); self.thread.start()

    def put(self, value):
        while not self.closed:
            try: self.queues[0].put(value,timeout=.2); return
            except queue.Full: continue

    def feed(self):
        try:
            while not self.closed:
                content = self.decoder.stdout.read(8192*8)
                if not content: break
                if len(content)%8: raise ValueError('Incomplete PCM frame from decoder')
                self.frames += len(content)//8
                self.put(content)
            if self.decoder.wait(timeout=10): raise ValueError('音乐解码失败。')
            self.put(None)
        except Exception as error:
            self.put({'error': str(error)}); self.put(None)

    def __iter__(self):
        while True:
            try: content = self.queues[-1].get(timeout=1)
            except queue.Empty:
                if any(p.exitcode not in (None,0) for p in self.processes): raise ValueError('Sony 并行工作进程退出。')
                continue
            if content is None: return
            if isinstance(content, dict):
                if 'error' in content: raise ValueError(content['error'])
                self.imports.update(content.get('imports',[]))
                continue
            yield content

    def close(self):
        self.closed = True
        for process in self.processes:
            if process.is_alive(): process.terminate()
        for process in self.processes: process.join(timeout=2)
        for pipe in self.queues: pipe.cancel_join_thread(); pipe.close()
