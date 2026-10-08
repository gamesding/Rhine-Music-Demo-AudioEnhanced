# Sony ARM → x86-64 C++

Windows 播放的 DSEE AI（DSX 3.0.7）、DCフェーズリニアライザー与バイナルプロセッサー使用这里的 C++ 转写。来源是固定 SHA-256 的 Sony DMP-Z1 1.02 音频库，AI 模型、配置、系数与黑胶预设保持原版。派生 Sony 内容不改授 MIT，见 [NOTICE](../../NOTICE.md)。

`generated/page_*.cpp` 包含按地址分组的原指令及对应 C++ 语句，保留原地址、原指令字节和反汇编注释。`dispatch.cpp` 连接这些已经编译的代码块，运行时不解码 ARM 指令。32 位指针、整数溢出、条件标志、VFP／NEON 寄存器位模式及数据布局由 `arm-state.hpp` 保持；`lift-host.cpp` 提供内存和调用 ABI。原数学库的相关代码也被转写，以保留原运算顺序与舍入。

这是二进制指令的 C++ 转写，并非恢复了 Sony 原始源码。原库仍提供只读常量、模型和重定位数据；不会用自制均衡器、谐波生成器或新神经网络替代。Windows 运算不依赖 ARM 模拟器，嵌入式 Python 仅负责 ABI 传输、分块和进程编排。

## 编译和验证

```powershell
$env:RHINE_CXX = "$PWD\.tools\windows-build\zig\zig-x86_64-windows-0.15.2\zig.exe"
npm.cmd run build:sony
npm.cmd run check:sony
```

编译使用 `-O2 -fno-fast-math -ffp-contract=off`，避免把非融合乘加变为 FMA。只有原来的融合指令使用融合运算。编译前逐位置核对三个原 ELF 的代码字节与全部生成 C++ 注释，校验九个 Sony 文件的 SHA-256。生成 `vendor/sony-walkman-x86/sony-dsp-x86.dll` 和包含指令图、源文件／DLL 哈希的清单。一键 EXE 构建包含编译及完整对照；打包器拒绝未重新编译的 C++ 源码或变动的指令图。

`check:sony` 自动准备固定版本的 64 位 Python 和 Unicorn 对照环境，不需安装系统 Python。对照用独立 ARM 实例和独立 C++ 实例，比较完整 PCM 字节与全部已分配处理状态。246 组覆盖 44.1／48 kHz 的所有音效组合、176.4／192 kHz 的相位／黑胶组合，以及静音、单声道脉冲、噪声和微小幅度信号。共 5,046,272 个输出值逐位一致。[机器可读结果](../../docs/SONY-X86-VERIFICATION.json)保留各组参数、PCM 哈希和耗时。

真实 ALAC 的十秒片段也逐位一致，本机三效果串行处理从约 18.22 秒降至 3.31 秒。多进程播放及短缓冲另行实测；不同设备与负载的速度会变化。

## 重新生成

`instructions.json` 保存原指令元数据；转写器只使用 Python 标准库：

```powershell
python -B scripts/sony-walkman/lift.py --trace native/sony/instructions.json
```

随后重新 `build:sony`、`check:sony`。采集和扩展控制流的研究脚本保存在 `research/`，需要 Capstone 及原 ARM 对照环境；它们不参与日常 EXE 构建。未转写的地址、未知导入或无效内存访问会明确失败，不会静默退回模拟器或关闭音效。

相位器的左右历史由桥接独立管理，分别调用同一 Sony 内核。与原版连续单声道入口对照可避免原双声道包装入口共用历史的串扰。这是声道状态修复；不改变系数和滤波运算。详见 [24 组声道测试](../../docs/SONY-PHASE-VERIFICATION.json)。本验证覆盖已支持的 PCM 路径，不包括 Walkman 的 DAC、放大器、全部固件功能或未知外设。
