// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 作者：江南的茶叶有甜 (zsimline@163.com)

#ifndef WALKFIRE_CORE_WALKFIRE_H
#define WALKFIRE_CORE_WALKFIRE_H

#include "videometa.h"
#include "m3u8parser.h"
#include "downloader.h"

namespace wfire {

// 视频源信息对象
VideoMeta videometa;  

// 多线程下载器
Downloader downloader;

// M3U8文件解析器
M3U8Parser m3u8parser;

// 下载 M3U8 文件
// 如果下载的文件不是最终包含TS文件链接的M3U8文件，
// 而是指向了一个M3U8备份文件，则去下载这个备份文件
// @param next_url 下一个将被下载的文件的链接
// @param cache_path_m3u8 M3U8文件的缓存目录
string DownloadM3U8(string next_url, const string &cache_path_m3u8);

// 设置M3U8文件版本
void SetExtXVersion();

// 设置播放列表第一个流媒体片段的序列号
void SetExtXMediaSequence();

// 设置每个视频分段最大的时长
void SetExtXTargetDuration();

// 向流媒体片段列表追加一个片段
void AppendTS();

// 设置视频源信息
void SetVideoMeta(const string &m3u8_filepath);

void DownloadTS();

}  // namespace wfire

#endif
