// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 通用公共函数库文件

#include "common.h"
#include <dirent.h>
#include <sys/stat.h>
#include <chrono>
#include <sstream>

using std::string;

namespace wfire {

namespace utils {

void CheckDir(const string &dir) {
  DIR *directory = NULL;
  directory = opendir(dir.c_str());
  if(directory == NULL)
    mkdir(dir.c_str(), S_IRWXU);
}

string MakeFilename(string suffix) {
    std::chrono::milliseconds ms = 
    std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    std::stringstream ss;
    ss << ms.count();
    return ss.str() + suffix;
}

string SpliceUrl(string url1, string url2) {
  int index = url1.find_last_of('/');
  url1.erase(index + 1, url1.size() - index);
  url1.append(url2);
  return url1;
}

}  // namespace utils

}  // namespace wfire
