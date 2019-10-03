// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 全局状态文件

#include "global.h"
#include <dirent.h>
#include <sys/stat.h>
#include "cmdline.h"

using std::string;

namespace wfire {

void Global::CheckDir(const string &dir) {
  DIR *directory = NULL;
  directory = opendir(dir.c_str());
  if(directory == NULL)
    mkdir(dir.c_str(), S_IRWXU);
}

Global::Global(int argc, char *argv) {
  std::map<string, string> parameters(ParseCmd(argc, argv));
  start_url_ = parameters["url"];
  filename_  = parameters["filename"];
  workspace_ = parameters["workspace"] + "/";
  cache_path_ = workspace_ + "cache/";
  cache_path_m3u8_ = cache_path_ + "m3u8/";
  cache_path_ts_ = cache_path_ + "ts/";
}

void Global::Init() {
  // 检查工作目录是否存在
  CheckDir(workspace_);
  CheckDir(cache_path_);
  CheckDir(cache_path_m3u8_);
  CheckDir(cache_path_ts_);
}

}  // namespace wfire
