# Rhine Music · Windows 增强版

基于 V0.3.0 的私人音乐播放器：用三维玻璃 CD 盒浏览本地与 FTP 收藏，在独立桌面窗口中播放，由 C++ 音频进程负责解码及 WASAPI／ASIO 输出。

音乐适配与维护：[RonaldDeng](https://github.com/RonaldDeng) · 上游：[LBEILC / RhineLabUI](https://github.com/LBEILC/RhineLabUI)

本轮更新日期：2026-10-08。当前为私有增强源码与 Windows x64 EXE，未公开发布新的 Release；此前的 [V0.3.0 macOS 发行](https://github.com/RonaldDeng/Rhine-Music-Demo/releases/tag/v0.3.0)属于历史版本。

## 本轮更新了什么

| 更新 | 实际行为 |
| --- | --- |
| 单文件桌面播放器 | 生成 `release/Rhine Music.exe`。自带窗口、音频组件及 Sony 执行环境，使用者无需安装 Node.js、Python、Unicorn 或 FFmpeg。 |
| C++ 原生音频 | 歌曲不经过 HTMLAudio／Web Audio；默认 WASAPI 共享输出，设置支持厂家 ASIO 驱动、输出声道和设备刷新。界面仍由 Electron 承载既有 Three.js 场景。 |
| Sony 原版音效 | DSEE AI、DCフェーズリニアライザー、バイナルプロセッサー的 ARM 指令转写并编译为 x86-64 C++。原模型、参数及系数保留，246 组完整链路的 PCM 和内部状态逐位一致。 |
| 多核与边算边播 | 原生流式解码与 C++ 运算同时进行，约半秒音频缓冲后起播，最多三个处理进程；切换音效从当前播放位置运算，及时取消旧任务。 |
| 相位器声道隔离 | 修复左右共用历史造成的串扰；六种模式、四种采样率的双向串扰为零，与 Sony 原版单声道入口逐位一致。 |
| DSD | DSF、未压缩 DFF 支持转 PCM、ASIO 原生 DSD或 DoP。数字直出自动旁路 Sony 音效、数字音量及淡入淡出。 |
| DSF ID3 | 读取 ID3v2.3／v2.4 中文标题、歌手、专辑、专辑歌手、曲号／碟号及内嵌封面；标签不会混入 DSD 载荷。 |
| FTP／FTPS | 只读扫描，所选歌曲下载到本机缓存后播放。下载后读取原音源参数、标签及封面，重扫、重启保留已识别信息；扫描不下载整库。 |
| Pad 触摸 | 平板横竖屏控件至少 44px，详情及设置可滚动，滑尺支持轻点和水平滑动；返回按钮位于品牌下方。 |
| Liquid Glass 播放条 | Apple Music 风格的浮动玻璃胶囊：左侧播放／切歌、中间封面与曲目／进度、右侧音量与当前曲目入口。实时折射三维场景，线性流光、按压高光、封面交替淡入，图标严格居中；暖昼／深夜与 Pad 横竖屏适配。 |
| 进度与触摸操作 | 已播／总时长、Sony 已生成区段和音量随播放显示；拖动先预览，松手只提交一次跳转。原生 DSD／DoP 音量显示 DAC 并锁定。减少动态效果会停止流光与交互光效。 |
| 前端刷新恢复 | 排序、扫描完成或页面刷新后，重新接回同一原生播放会话，恢复歌曲、队列、位置、暂停状态、音量和 Sony 处理状态；拦截旧页面的迟到控制，避免后台有声音而前台显示未播放。 |
| 技术标志 | 当前歌曲实际启用哪些 Sony 效果就显示哪些透明 SVG；线性进入、扫光及黑胶旋转兼顾暖昼／深夜主题，暂停或减少动态效果时静止。 |
| Hi-Res 与金边彩蛋 | 使用 `art` 中的原 SVG，曲目格式旁显示源音质标志；每首都符合的专辑在浏览／详情标题右侧显示标志，玻璃盒左右镶同款金色。恒速扫光兼顾暖昼、深夜和减少动态效果。 |
| DSD 双标志 | DSD 音源同时显示 Hi-Res 和原 DSD SVG；全 DSD 专辑在浏览／详情显示双标志和金边。DSD 标志透明背景，暖昼石墨色／深夜银白色，金色扫光保持线性；转 PCM 播放仍按原音源显示。 |
| DFF 参数读取 | 修复标签库未跳过奇数数据块填充字节的问题，正确读取未压缩 DFF 的采样率、位深、声道和时长。 |
| 24 bit／192 kHz ALAC | 从 ALACSpecificConfig 读取真实分辨率，自动升级旧索引；曲目和全 Hi-Res 专辑恢复标志及金边。高采样率保留原采样率，逐项旁路不支持的 Sony 效果。 |
| 动画停顿与界面比例 | 封面图集常驻显存，只上传变化区域，并避免大画布回读；玻璃、阴影及后处理在进场计时前预热。76 张合成专辑同画质实测，滚动约 13 → 97 FPS、打开详情约 5 → 98 FPS。桌面优先使用独立显卡，启动／刷新恢复 100% 页面比例，画质设置继续沿用。 |
| FiiO ASIO 实测 | 修正原生 DSD 的显式声道格式／立体声回调；已连接设备的 192 kHz PCM、DSD64 原生和 DoP 完成启播、暂停、跳转和停止验证。 |
| 启动与 DSF 修正 | 正常刷新取消加载时不再弹出 `ERR_ABORTED` 启动失败；修正已测到的 DSF 最后完整块漏读，完整 DSD／DoP 载荷已比较。 |

Sony AI 来源为 [Sony 官方 DMP-Z1 1.02 固件](https://www.sony.jp/audio/update/pc_update_dmp-z1.html)中的 DseeAi／DSX 3.0.7。

Windows 播放使用 C++ 运算，不再运行 ARM 模拟器。真实 ALAC 十秒片段的三效果输出和内部状态也与原版逐位一致，处理时间从 18.22 秒降至 3.31 秒；这台主机的二十秒音频约 0.89 秒开始原生播放。五分钟曲目从第 180 秒切换音效，约 0.67 秒完成起播缓冲。详见 [源码与验证](native/sony/README.md)、[Sony 说明](docs/SONY-WALKMAN.md)。

本轮另做三项全开／全关及单项实际输出的频谱测量，使用同一绝对标尺；相位器另测合成脉冲的幅度和相位，说明见 [Sony 输出测量](docs/SONY-AUDIO-MEASUREMENTS.md)。个人音乐和生成的音频片段不进入源码或 EXE。

## 直接使用 EXE

1. 将 **`Rhine Music.exe`** 保存到本机，双击打开。
2. 在「音乐库」填写完整音乐目录，每行一个，保存并扫描。例如 `D:\Music` 或 `\\NAS\music`。
3. 打开专辑，点击曲目播放；设置中选择输出方式、Sony 音效、主题及画质。FTP 音乐在设置中填写连接信息，测试后保存并扫描。

播放后底部显示 Liquid Glass 浮动播放条，可触摸拖动进度、查看时间、暂停、切歌和调节音量。暖昼／深夜使用对应的透明玻璃色调，Pad 竖屏调整为两行；封面与文字线性进入，玻璃边缘恒速流光并响应触摸。实时折射复用现有三维场景的最终输出，无额外场景重绘或像素回读；减少动态效果保留静态玻璃与全部操作。图标居中的铁律记录在 [Memory.md](Memory.md)。

拖动时只预览，松手才跳转；Sony 正在处理时还显示已经生成的音频区段。点击顶部、底部歌名或底栏的当前曲目入口可打开所属专辑并定位曲目，已接入当前音源的 Sony 技术标志显示在详情中。排序或扫描触发的页面刷新会恢复正在进行的原生播放；关闭整个 EXE 仍停止播放。

首次将自带运行文件展开到 `%LOCALAPPDATA%/RhineMusic/runtimes/<内置包哈希前32位>/`，以后复用。搬移程序只需搬移 EXE；关闭窗口会停止它拥有的音频、处理进程和本地服务。EXE 不含用户歌曲、配置、缓存或凭据。

用户数据默认位于 `%APPDATA%/Rhine Music/`：曲库、FTP 凭据与音频缓存放在 `music-data/`，界面偏好在 `preferences.json`。升级先关闭程序再替换 EXE。读取歌曲和标签不改写原文件；FTP 不执行写入或删除。详见 [Windows 使用说明](docs/WINDOWS.md)。

## ASIO 与 DSD 设置

接入 DAC、安装厂家 ASIO 驱动后，在「音频输出」点击「停止播放并刷新设备」，选择驱动、第一输出通道和 DSD 播放方式。没有驱动时显示未找到驱动，不自动安装厂家驱动或伪造设备。

| 输出路线 | Sony 音效 | 数字音量／淡入淡出 |
| --- | --- | --- |
| PCM → WASAPI／ASIO | DSEE：44.1／48 kHz；DC／黑胶：44.1、48、176.4、192 kHz | 支持 |
| DSD → 44.1 kHz PCM → WASAPI／ASIO | 支持 | 支持 |
| DSD → ASIO 原生 DSD | 旁路 | 锁定／旁路 |
| DSD → ASIO DoP | 旁路 | 锁定／旁路 |

DoP 仍承载 DSD，不能加 PCM 音效；需要效果请选择转 PCM。原生 DSD／DoP 不混音、不重采样，设备拒绝精确采样率或格式时明确报错。DSEE AI 原版不接受 192 kHz 输入，播放器保留源采样率、旁路这一项并显示说明；相位和黑胶继续处理，标志只显示实际运行的效果。DST 压缩 DFF 未支持；WASAPI 共享输出可能由系统重采样。

2026-10-08 已在接入的 FiiO ASIO 驱动上验证 192 kHz PCM，以及合成静音 DSD64 原生／DoP 的启播、暂停、跳转、停止；真实 DSF 验证原生打开及跳转，真实 24／192 ALAC 验证原版 DC／黑胶的 ASIO 播放。DSD128／256 目前仅查询到驱动支持，热拔插与长期稳定性尚未覆盖。详见 [实际验证](docs/UI-REVIEW-V0.3.0.md)。

## Hi-Res 音源标识

按 [JAS／JEITA 的音源定义](https://www.jas-audio.or.jp/hi-res/definition)判断原文件：无损 PCM 至少 44.1 kHz／16 bit，并且采样率高于 48 kHz 或位深大于 16 bit；DSF／DFF 的 DSD64 及以上也显示标志。例如 24 bit／44.1 kHz、24 bit／48 kHz、16 bit／96 kHz 符合，16 bit／44.1 kHz 和 16 bit／48 kHz不显示。

专辑必须非空且每首均符合；混合专辑只标符合的曲目。未知参数和有损音源不标记，DSEE 输出升频不改变源文件的判定。FTP 下载所选曲目后读取参数，已识别结果可跨重扫／重启保留。标志反映文件参数，不验证录音母带或认证播放设备。判定、线性动画与玻璃金边的实现和来源见 [Hi-Res 说明](docs/HI-RES.md)。

DSD64 及以上源文件同时显示 Hi-Res 和 DSD。整张专辑每首都是 DSD 时，标题右侧也显示双标志；DSD 与 PCM 混合的全 Hi-Res 专辑只显示 Hi-Res 专辑标志，DSD 曲目仍有双标志。原 SVG 透明轮廓兼顾暖昼／深夜，恒速扫光支持减少动态效果。选择转 PCM 不会丢失源文件的 DSD 标记。

## 一键编译成单独 EXE

在 **Windows x64** 完整解压源码，双击根目录的 **[Build-Windows-EXE.cmd](Build-Windows-EXE.cmd)**。

脚本自动下载并校验便携 Node.js 26.7.0 和 Zig 0.15.2，放在工程的 `.tools/windows-build/`，不写入系统 PATH、不全局安装开发环境。然后安装锁定 JS 依赖，重新编译 C++，运行检查，构建界面并打包。首次需要联网下载 npm 依赖和固定版本 Electron、嵌入式 Python、Unicorn；之后工具及运行包可复用。预留至少 3 GB 可用空间，完整工程路径尽量简短。

也可以从 PowerShell 执行同一个流程，无需预先安装 Node.js 或 Zig：

```powershell
Set-Location -LiteralPath 'C:\Projects\Rhine-Music-Demo-Enhanced'
powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\scripts\build-windows.ps1
```

失败立即停止并显示出错命令；只有构建和隔离 EXE 自检全部通过，才显示完成。双击入口会保留终端供阅读结果。Windows 内置 .NET Framework 编译器用于单文件启动器；无需 Visual Studio、系统 Python 或 FFmpeg。

生成物：

- `release/Rhine Music.exe`：交付给使用者的唯一必要文件。
- `release/Rhine Music.exe.sha256`：EXE 校验值。
- `release/desktop-build.json`：版本、组件来源、包大小及哈希。
- `release/desktop-package-verification.json`：独立 EXE 的实际检查结果。
- `release/Rhine-desktop-payload.zip`：内部运行文件包，研究或排错可用，日常运行不需要放在 EXE 旁。

一键构建会重新生成上述文件；不会自动提交、推送或发布仓库。

## 逐条编译命令

下面使用脚本下载的同一套便携工具，便于修改源码后逐步检查。先进入工程并仅准备工具：

```powershell
Set-Location -LiteralPath 'C:\Projects\Rhine-Music-Demo-Enhanced'
powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\scripts\build-windows.ps1 -PrepareOnly

$env:PATH = "$PWD\.tools\windows-build\node\node-v26.7.0-win-x64;$env:PATH"
$env:RHINE_CXX = "$PWD\.tools\windows-build\zig\zig-x86_64-windows-0.15.2\zig.exe"
node --version
npm.cmd --version
```

安装锁定依赖并编译原生主机：

```powershell
npm.cmd ci
npm.cmd run build:native
npm.cmd run build:sony
npm.cmd run check:sony
npm.cmd run check:native
npm.cmd run check:audio
npm.cmd run check:hires
```

运行曲库、界面与内容检查，然后构建前端：

```powershell
npm.cmd run check:music
npm.cmd run check:content
npm.cmd run check:viewport
npm.cmd run build
```

打包已有构建，并实际运行隔离测试：

```powershell
npm.cmd run package:windows -- --skip-build
node .\scripts\check-windows-package.mjs
Get-FileHash -LiteralPath '.\release\Rhine Music.exe' -Algorithm SHA256
```

仅前端改动可保留已匹配哈希的 C++ 主机；改动 `native/audio-host.cpp` 后必须重新 `build:native`，改动 `native/sony/` 的 C++ 后必须重新 `build:sony` 并运行 `check:sony`。一键脚本包含这两个编译步骤和 246 组原 ARM／C++ 对照。打包器会核对 C++ 源码／二进制、原生 DLL、九个 Sony 文件及自带运行时哈希，缺文件或不一致时拒绝打包。工具来源固定在 [windows-build-tools.json](scripts/windows-build-tools.json)与 [runtime-assets.json](desktop/runtime-assets.json)。

独立 EXE 自带的诊断入口也可手动运行：

```powershell
& '.\release\Rhine Music.exe' --self-test --report "$PWD\release\self-test.json"
```

`check-windows-package.mjs` 会只复制一个 EXE 到带中文及空格的隔离目录，把 PATH 限制为 Windows 系统目录，检查自带解码器、DSF ID3、完整 DSD／DoP 载荷、Sony 三效果处理及静音 WASAPI 播放，并再次启动确认缓存复用。该测试不会读取用户曲库。

## 已验证与尚未覆盖

- 原版神经网络入口、各效果预设、串行／并行一致性、增长 WAV 的处理及实际原生输出有执行证据。
- DSF／DFF 的 DSD64、128、256，块边界、位序、声道及 DoP 标记和全部测试载荷已比较；DSF 中文 ID3、封面、源文件不变和 FTP 重扫／重启有检查。
- 使用隔离生成音频、内置示例封面与本机 FTP 服务进行实际桌面窗口、主题和 Pad 触摸回归；[具体尺寸、截图、性能及限制](docs/UI-REVIEW-V0.3.0.md)按实际结果记录。
- 当前 EXE 未签名；Windows 10、Windows ARM、真实 iPad、其他厂商 ASIO／DSD DAC、公网 FTP／实际 FTPS、整库全格式与长期压力测试尚未验证。

本地服务只监听 `127.0.0.1`，保留 Host／Origin 校验和只读音乐边界；触摸适配不包含另一台 iPad 经局域网访问电脑的部署。多核不代表强行占满 CPU，本机快于实时的样本结果也不保证所有曲目或负载都能实时。

## 开发与历史资料

| 资料 | 内容 |
| --- | --- |
| [Windows 说明](docs/WINDOWS.md) | 输出路线、数据位置、构建与验证 |
| [Sony 桥接说明](docs/SONY-WALKMAN.md) | 原版来源、C++ 转写、声道隔离、实时起播与验证边界 |
| [C++ 原生源码](native/README.md) | 音频主机与完整音效链的 x86 指令转写 |
| [界面验证记录](docs/UI-REVIEW-V0.3.0.md) | 本轮实际检查及历史记录 |
| [音乐服务](docs/MUSIC-SERVICE.md) | 曲库、索引、只读接口 |
| [在线曲库](docs/ONLINE-LIBRARY.md) | 既有 Internet Archive／Subsonic 功能，原生桌面输出当前限本地与 FTP 音源 |
| [设计](DESIGN.md)、[更新历史](CHANGELOG.md) | 既有三维界面及版本演进 |
| [历史 V0.3.0 发布](docs/RELEASE-V0.3.0.md) | 2026-10-01 macOS 源码发行检查 |

既有 macOS 源码入口 `启动音乐播放器.command`、原版档案 `?original=1`、旧导航 `?nav=previous` 和共享资源保留；本轮 Windows 原生组件不表示 macOS 原生 ASIO／DSD 已适配。

## 法律信息

音乐适配与后续修改：**Copyright (c) 2026 RonaldDeng**。上游 RhineLabUI：**Copyright (c) 2026 LBEILC**。有权授权的应用代码、建模脚本及技术文档沿用 [MIT License](LICENSE)，保留 Git 历史、上游署名和 [原版说明](README.original.md)。

Sony 音效由 `Sony Corporation` 提供。DSEE、S-MASTER 是 `Sony Corporation` 的商标。

© 2026 Sony Corporation

本项目自行实现桌面桥接与播放器界面，Sony 原版二进制、模型、参数、商标及派生研究不改授 MIT。Un4seen BASS／ASIO／DSD 组件适用各自的免费非商业使用条款；Unicorn 原生引擎保留 GPL 许可和对应源码，Electron、Python、字体及 JS 依赖保留原许可。

《明日方舟》及相关名称、视觉、标志和原 PV 采样归各权利人所有，代码 MIT 不自动覆盖这些素材。完整来源、第三方许可、随包文本及边界见 [NOTICE.md](NOTICE.md)。个人歌曲、商业封面、索引、缓存、配置及凭据不入库、不打包。
