// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 全局状态文件

#include "global.h"
#include <dirent.h>
#include <sys/stat.h>
#include "cmdline.h"

using std::string;

namespace wfspace {

void Global::CheckDir(const string &dir) {
  DIR *directory = NULL;
  directory = opendir(dir.c_str());
  if(directory == NULL)
    mkdir(dir.c_str(), S_IRWXU);
}

Global::Global(int argc, char *argv[]) {
  std::map<string, string> parameters(ParseCmd(argc, argv));
  starturl_ = parameters["url"];
  filename_ = parameters["filename"];
  workspace_ = parameters["workspace"] + "/";
  cache_path_ = workspace_ + "cache/";
  cache_path_m3u8_ = cache_path_ + "m3u8/";
  cache_path_ts_ = cache_path_ + "ts/";
  threads_ = stoi(parameters["threads"]);
}

Global::~Global() {}

void Global::Init() {
  CheckDir(workspace_);
  CheckDir(cache_path_);
  CheckDir(cache_path_m3u8_);
  CheckDir(cache_path_ts_);
}

void Global::set_starturl(string starturl) {
  starturl_ = starturl;
}

void Global::set_m3u8_filepath(string m3u8_filepath) {
  m3u8_filepath_ = m3u8_filepath;
}

string Global::starturl() const {
  return starturl_;
}

string Global::cache_path_m3u8() const {
  return cache_path_m3u8_;
}

string Global::cache_path_ts() const {
  return cache_path_ts_;
}

string Global::m3u8_filepath() const {
  return m3u8_filepath_;
}

int Global::threads() const {
  return threads_;
}

}  // namespace wfspace
