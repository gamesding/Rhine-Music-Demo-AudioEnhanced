# Windows 私有增强版 · 2026-10-08

本轮按用户追加要求提供单文件 `release/Rhine Music.exe`。自带 Electron 独立窗口、C++ 原生音频、Sony ARM 指令转写的 x86-64 C++ 音效与九个 Sony 原版运行文件；使用者无需安装 Node.js、Python、FFmpeg 或编译工具。既有三维界面保留，歌曲解码和设备输出交给原生进程。嵌入式 Python 编排处理流水线；Unicorn 保留用于原 ARM 对照，播放时不执行 ARM 模拟。

## 使用

双击 EXE，首次将内置运行文件展开到 `%LOCALAPPDATA%/RhineMusic/runtimes/<payload-sha256-前32位>/`，以后复用。只需移动 EXE，无需复制旁边的环境。关闭窗口会停止它拥有的音频、Sony 工作进程和本地服务。

在「音乐库」填写本地音乐的完整路径并扫描，或在设置里的 FTP 音乐库填写连接信息、测试、保存并扫描。FTP／FTPS 为只读访问，FTPS 校验证书；SFTP 未支持。所选 FTP 曲目下载至本机缓存后播放，能够使用原生输出和 Sony 音效。

曲库、FTP 凭据、缓存及偏好默认在 Electron 用户数据目录 `%APPDATA%/Rhine Music/`。开发验证可用 `MUSIC_DATA_DIR`、`RHINE_APP_HOME` 分离数据，`RHINE_RUNTIME_ROOT` 指定自带运行时缓存。升级只需关闭窗口并替换 EXE；用户数据不进入程序包，歌曲标签不会被改写。

## 原生输出

默认原生 WASAPI 共享输出。设置可选择 ASIO、厂商驱动、输出声道与 DSD 路由；未安装驱动时显示未找到驱动，不虚构设备。接入 DAC 并安装厂商 ASIO 驱动后，点击「停止播放并刷新设备」再选择。

| 音源／路由 | Sony 音效 | 数字音量／淡入淡出 |
| --- | --- | --- |
| PCM → WASAPI／ASIO | DSEE：44.1／48 kHz；DC／黑胶：44.1、48、176.4、192 kHz | 支持 |
| DSD → 44.1 kHz PCM → WASAPI／ASIO | 支持 | 支持 |
| DSD → ASIO 原生 DSD | 旁路 | 锁定／旁路 |
| DSD → ASIO DoP | 旁路 | 锁定／旁路 |

DoP 仍承载原始 DSD 位流，不能加 PCM 音效。原生 DSD／DoP 不混音、不重采样；精确采样率或格式不被设备接受时明确报错。支持 DSF 和未压缩 DFF，未支持 DST。WASAPI 系统输出可能重采样，文件采样率不代表 DAC 实际输出率。

DSF 支持文件尾部 ID3 标签。本地索引已验证 ID3v2.3／v2.4 的中文标题、歌手、专辑及专辑歌手、曲号、碟号和内嵌 PNG 封面，缓存重载和封面接口保留相同内容。标签加入前后的全部原始 DSD 字节及 DoP 载荷相同；读取和播放不会改写源文件。参见 [Sony DSF 规范](https://dsd-guide.com/sites/default/files/white-papers/DSFFileFormatSpec_E.pdf)。FTP 扫描阶段以远端文件名展示，选择 DSF 下载后从本机缓存读取标签和封面，随后更新界面；不为标签下载整库。重扫、重启和清理音频缓存后保留已识别的文字标签。

Sony 首次处理保留原版连续状态与最多三个工作进程，缓存可复用。x86 C++ 完整输出和内部状态通过 246 组逐位对照；相位器 24 组独立左右声道测试均通过。处理从当前播放位置开始，约半秒音频即可起播；本机首缓冲实测约 0.59–0.89 秒，音效切换约 0.67 秒。CPU 使用由启用阶段决定，不人为占满空闲核心。具体证据与覆盖范围见 [Sony 说明](SONY-WALKMAN.md)。

播放后底部显示 Liquid Glass 浮动胶囊：左侧切歌／播放，中间原专辑封面与歌名／进度，右侧音量与当前曲目入口。玻璃实时折射三维场景，边缘高光、流光、按压与封面淡入均采用线性时间；暖昼／深夜自动适配，Pad 竖屏使用两行布局。减少动态效果停止光效动画，保留静态玻璃和控制。着色器与现有最终输出合并，不增加场景重绘、WebGL 上下文、离屏目标或 GPU 像素回读。

已播／总时长、Sony 缓冲区段与音量随播放更新。Pad 拖动先预览，松手只提交一次跳转；取消拖动不改位置，暂停时跳转仍保持暂停。原生 DSD／DoP 音量显示 DAC 并锁定。点击顶部或底部歌名以及当前曲目入口可进入所属专辑并定位曲目，详情显示实际启用的 Sony 技术 Logo。图标居中要求见 [Memory.md](../Memory.md)。

排序设定、扫描完成或手动页面刷新后，新页面接回同一原生音频会话，恢复歌曲、队列、进度、暂停状态、设定音量和 Sony 处理信息。旧页面的迟到请求不能重新打开或停止已接回的会话。若当前曲目已经从索引移除，停止无法恢复的原生输出并提示；关闭整个 EXE 仍正常停止播放。

Hi-Res 音源在曲目格式左侧显示原 SVG 标志，整张专辑均符合时在浏览／详情标题右侧显示，并为玻璃盒左右边框镶金。根据原文件无损采样率／位深及 DSD 参数判定；DSEE 输出升频不改变标记。FTP 下载后读取原参数，未知曲目不猜测。线性扫光支持暖昼／深夜，减少动态效果时静止。标准与检查见 [Hi-Res 说明](HI-RES.md)。

DSD64 及以上曲目同时显示 Hi-Res 与 DSD 原 SVG；每首都是 DSD 的专辑在标题旁显示双标志与金边。DSD 与 PCM 混合的全 Hi-Res 专辑只保留 Hi-Res 专辑标志，DSD 曲目仍显示两者。DSD 标志透明背景，暖昼石墨色／深夜银白色、线性金色扫光；转 PCM 播放不改变源文件标记。

## 构建与验证

运行根目录 `Build-Windows-EXE.cmd` 可一键准备便携工具、编译两个 C++ 组件、验证并生成 EXE。详细逐条命令见 [README](../README.md)。已有工具时执行 `npm ci`、`npm run build:native`、`npm run build:sony`、`npm run check:sony`、`npm run check:audio`、`npm run check:hires`、`npm run check:native`、`npm run build`，随后 `npm run package:windows -- --skip-build`。`RHINE_CXX` 可指定 Zig 0.15.2；打包器校验 C++ 源码与编译产物一致。

打包入口 [package-desktop.mjs](../scripts/package-desktop.mjs)固定下载并校验 [运行时清单](../desktop/runtime-assets.json)，也校验 Sony、原生 DLL／EXE 和对应 C++ 源码。仅安装生产 JS 依赖，不收集个人歌曲、配置或缓存。单文件封装为 [Standalone.cs](../windows/Standalone.cs)，内置 ZIP 校验后在受控目录展开。

`node scripts/check-windows-package.mjs` 验证单独复制的 EXE、精简 PATH、自带 x86 C++ Sony 执行、24 组相位隔离、DSF 标签及原始 DSD／DoP 字节、解码和静音输出，共六项。EXE 自带 `--self-test --report <json-file>`。桌面渲染和 Pad 触摸记录见 [UI 验证](UI-REVIEW-V0.3.0.md)。

已连接 FiiO ASIO 驱动并查询实际支持的时钟／格式。192 kHz PCM 与合成静音 DSD64 原生／DoP 的启播、暂停、跳转、停止通过；真实 DSF 原生打开／跳转及真实 ALAC 的原版相位／黑胶播放通过。DSD128／256 仅查询了能力；热拔插、长期稳定性和主观听音尚未验证。EXE 未做代码签名，Windows 10／ARM 和真实 iPad 未验证。各第三方组件保留原许可，详见 [NOTICE](../NOTICE.md)。本私有增强包未公开发布。

24／192 ALAC 的旧参数会在启动重扫时自动修正，恢复曲目／专辑 Hi-Res 标志。DSEE 原版只接受 44.1／48 kHz 输入，高采样率自动旁路该项并保持原采样率；相位与黑胶可以在 176.4／192 kHz 运行。动画使用图集局部上传、避免大画布回读并在进场前预热；画质缩放只改变渲染缓冲。启动／刷新恢复 100% 页面比例，Windows DPI 缩放继续由系统处理。
