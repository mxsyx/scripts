// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 通用公共函数库文件

#ifndef WALKFIRE_CORE_UTILS_H_
#define WALKFIRE_CORE_UTILS_H_

#include <string>

namespace wfire {

namespace utils {

// 判断目录是否存在
// 若不存在则新建目录
void CheckDir(std::string dir);

// 根据时间戳字符串生成文件名
// @param suffix 文件名后缀
std::string MakeFilename(std::string suffix);

}  // namespace utils

}  // namespace wfire

#endif  // WALKFIRE_CORE_UTILS_H_
