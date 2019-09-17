// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 全局状态文件

#ifndef _WFIRE_GLOBAL_H__
#define _WFIRE_GLOBAL_H__

#include <string>
#include "videometa.h"

namespace wfire {

std::string WORKSPACE = NULL;  // 工作目录
VideoMeta videometa;  // 视频源信息

} // namespace wfire

#endif // _WFIRE_GLOBAL_H__
