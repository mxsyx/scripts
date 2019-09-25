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


}  // namespace wfire

#endif
