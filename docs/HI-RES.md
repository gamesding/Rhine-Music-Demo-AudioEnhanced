# Hi-Res／DSD 音源标志与玻璃金边

本次增强日期：2026-10-08。使用用户提供的 `art/Hi-Res_Audio_(logo).svg`，原样复制到 `public/audio-tech/hi-res.svg`。没有重绘文字或转换为不透明位图。

DSD 标志使用用户提供的 `art/DSDlogo.svg`，原字节复制到 `public/audio-tech/dsd.svg`，用 SVG 透明轮廓作为 CSS 遮罩。暖昼使用石墨色，深夜使用银白色；恒速金色反射仅出现在标志轮廓内，不增加底板。

## 原音源判定

[日本音响协会 JAS 的定义页](https://www.jas-audio.or.jp/hi-res/definition)列出 JEITA 音源示例。44.1／48 kHz、16 bit 视为 CD 等级；24 bit／44.1 kHz、24 bit／48 kHz 和 16 bit／96 kHz 均属于 Hi-Res。32 kHz／24 bit 或 96 kHz／12 bit 不满足条件。设备标志还涉及 96 kHz／24 bit、模拟频响及听感评估；音源标记与设备认证不同。

据此，播放器对已识别的无损 PCM 要求 `sampleRate >= 44100`、`bitsPerSample >= 16`，并满足 `sampleRate > 48000 || bitsPerSample > 16`。原 DSD 源文件依据 [Sony 音源定义](https://www.sony.com/ja/SonyInfo/News/Press/201309/13-127/)，识别 DSD64（2.8224 MHz）及以上的 DSF／DFF。有损或参数未知的文件不自动标记。

判断使用索引中的原文件参数；Sony 处理输出、DSD 转 PCM 和系统重采样不会改写源参数。只能判断文件格式与分辨率，不能凭标签确认母带是否曾升频或设备是否实际按原规格输出。

24／192 ALAC 从原 [ALACSpecificConfig](https://github.com/macosforge/alac/blob/master/ALACMagicCookieDescription.txt) 读取位深和 32 位采样率，不采用可能只写了 16 bit／1 Hz 的旧 MP4 音频描述字段。仅按 atom 边界定位头部并跳过音频载荷；标签和原文件不改写。本地旧索引通过元数据版本升级重读，FTP 缓存读取时更新。已对用户授权的 9 首 24／192 ALAC 和 14 首 DSD64 的参数进行实际验证。

## 显示与动画

- 单曲标志位于歌单每行的格式左侧，约 21px；混合专辑保留逐曲结果。
- 非空专辑中每首都符合时，在浏览与详情标题右侧显示 40–54px 标志。为标志预留标题宽度，保留原字轮节奏、共用视口布局与 Pad 触摸控件。
- 标志保留 SVG 原金色，反射以 6.8 秒恒速横扫，边缘光晕线性往复；小标志为 9.6 秒较弱反射。暖昼使用薄阴影，深夜使用克制的金色光晕。设置或系统启用减少动态效果时停止动画。
- 全 Hi-Res 专辑的玻璃盒使用同款 `#DDC77C`／`#B4802C` 金色左右边框；复用既有 Blender 模型及实例批次。透明面板、封面尺寸、盒体尺寸及取景保持原实现。切换后的归还副本保留各自材质标识，普通专辑不会继承前一张的金边。
- DSD64 及以上曲目同时显示 Hi-Res 和 DSD。每首都是 DSD 的专辑在浏览／详情标题旁同时显示两个标志，并有 Hi-Res 金边。PCM 与 DSD 混合的全 Hi-Res 专辑只显示 Hi-Res 专辑标志，DSD 曲目仍有双标志。
- DSD 专辑标志以 8.4 秒、曲目标志以 12 秒线性扫光，主题色在 650ms 内线性切换。标题和曲目行预留双标志的宽度；设置或系统减少动态效果时停止动画，保留静态标志。转 PCM、DoP 或原生输出不会改变原文件的 DSD 身份。

FTP 扫描只列目录，参数在所选文件下载后读取，结果跨重扫和重启保留。尚未读取参数的歌曲不会凭扩展名猜测；整张专辑均已识别且符合时才出现专辑标志和金边。

## DFF 读取与检查

当前标签库在部分未压缩 DFF 中未跳过奇数长度块的填充字节。补充读取器按 [Philips DSDIFF 1.5 规范](https://www.sonicstudio.com/pdf/dsd/DSDIFF_1.5_Spec.pdf)校验边界并跳过填充，只读取头部／标签，跳过音频载荷。读取文件始终只读；不修改第三方依赖或源音乐。压缩 DST 解码仍未支持。

运行 `npm run check:hires` 检查官方边界、真实 PCM／DSD 元数据、DFF 填充及无效边界、全 DSD／混合／未知专辑和两个 SVG 原字节。`npm run check:audio` 包含 FTP 原参数持久化检查，`npm run check:music` 包含玻璃材质、独立金边上下文与归还副本检查。一键 EXE 构建自动执行这些检查；窗口实测记录见 [UI 验证](UI-REVIEW-V0.3.0.md)。

Hi-Res Audio 是 Japan Audio Society 的商标；该音源标识不表示设备认证。资源权利及 Sony 信息见 [NOTICE](../NOTICE.md)。
