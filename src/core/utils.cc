// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 公共函数库文件

#include "utils.h"
#include <dirent.h>
#include <sys/stat.h>
#include <chrono>
#include <sstream>

namespace wfire {

namespace utils {

void CheckDir(std::string dir) {
  DIR *directory = NULL;
  directory = opendir(dir.c_str());
  if(directory == NULL)
    mkdir(dir.c_str(), S_IRWXU);
}

std::string MakeFilename() {
    std::chrono::milliseconds ms = 
    std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    std::stringstream ss;
    ss << ms.count();
    return ss.str();
}
  
}  // namespace utils

}  // namespace wfire
