# 解码回归夹具

`alac-192.m4a.b64` 是 400 Hz、24 bit、192 kHz、双声道、0.06 秒的合成 ALAC，含合成标题和专辑标签，用于验证 ALACSpecificConfig、旧索引升级、Hi-Res 判定和原版 DC／黑胶高采样率处理。开发时生成命令：`ffmpeg -f lavfi -i sine=frequency=400:sample_rate=192000:duration=0.06 -ac 2 -c:a alac -sample_fmt s32p -metadata "title=Synthetic ALAC" -metadata "album=Synthetic Hi-Res" alac-192.m4a`。未采集音乐；用户曲库不进入夹具。

`aac-padding.m4a.b64` 是 997 Hz、48 kHz、双声道、0.237 秒的合成 AAC 音频，使用 FFmpeg AAC 编码器生成，未采集音乐。容器声明 11,376 个 PCM 帧，末尾不足一个 AAC 编码帧；用于验证 Windows Media Foundation 尾部填充不会延长流式 Sony 输入时间轴。Base64 仅便于源码分发，播放器不加载此测试文件。
