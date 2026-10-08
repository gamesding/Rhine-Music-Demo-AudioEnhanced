// Verify that every translated site comes from the pinned original ELF code.
import {promises as fs} from 'node:fs'
import path from 'node:path'
import {createHash} from 'node:crypto'
import assert from 'node:assert/strict'

export async function validateSonySourceGraph(project) {
  const hash = bytes => createHash('sha256').update(bytes).digest('hex')
  const manifest = JSON.parse(await fs.readFile(path.join(project, 'scripts/sony-walkman/assets.json'), 'utf8'))
  const files = new Map()
  for (const [name, expected] of Object.entries(manifest.files)) {
    const bytes = await fs.readFile(path.join(project, 'vendor/sony-walkman', name))
    assert.equal(hash(bytes), expected, `Original Sony asset changed: ${name}`)
    files.set(name, bytes)
  }
  const raw = await fs.readFile(path.join(project, 'native/sony/instructions.json'))
  const graph = JSON.parse(raw.toString('utf8'))
  assert.equal(graph.sourceSha256, manifest.files['libSoundServiceFw.so'])
  const segments = []
  for (const [base, name] of [[0x10000000, 'libSoundServiceFw.so'], [0x11000000, 'libm-2.23.so'], [0x12000000, 'libc++.so.1.0']]) {
    const elf = files.get(name)
    assert.equal(elf.subarray(0, 6).toString('hex'), '7f454c460101')
    assert.equal(elf.readUInt16LE(18), 40, 'Expected original ARM ELF')
    for (let i = 0; i < elf.readUInt16LE(44); i++) {
      const p = elf.readUInt32LE(28) + i * elf.readUInt16LE(42)
      if (elf.readUInt32LE(p) === 1 && (elf.readUInt32LE(p + 24) & 1)) {
        const start = base + elf.readUInt32LE(p + 8), length = elf.readUInt32LE(p + 16)
        segments.push({start, end: start + length, offset: elf.readUInt32LE(p + 4), elf})
      }
    }
  }
  for (const [key, site] of Object.entries(graph.instructions)) {
    assert.equal(Number(key), site.address)
    const bytes = Buffer.from(site.bytes, 'hex')
    assert.equal(bytes.length, site.size)
    const segment = segments.find(s => site.address >= s.start && site.address + site.size <= s.end)
    assert.ok(segment, `Translated address is outside original code: ${site.address.toString(16)}`)
    const offset = segment.offset + site.address - segment.start
    assert.ok(bytes.equals(segment.elf.subarray(offset, offset + site.size)), `Original instruction bytes differ at ${site.address.toString(16)}`)
  }
  const generated = path.join(project, 'native/sony/generated'), seen = new Set()
  const pages = (await fs.readdir(generated)).filter(name => /^page_[a-f0-9]+\.cpp$/.test(name))
  for (const file of pages) {
    const code = await fs.readFile(path.join(generated, file), 'utf8')
    for (const match of code.matchAll(/^L([a-f0-9]+):\{ \/\/ ([a-f0-9]+) /gm)) {
      const address = parseInt(match[1], 16), site = graph.instructions[String(address)]
      assert.ok(site, `Generated site missing from graph: ${match[1]}`)
      assert.equal(match[2], site.bytes)
      assert.equal(seen.has(address), false, `Duplicate generated site: ${match[1]}`)
      seen.add(address)
    }
  }
  assert.equal(seen.size, Object.keys(graph.instructions).length, 'Generated C++ does not cover the complete instruction graph')
  return {sourceSha256: graph.sourceSha256, instructionGraphSha256: hash(raw), instructionSites: seen.size, pages: pages.length, originalAssets: files.size, originalInstructionBytesVerified: true}
}
