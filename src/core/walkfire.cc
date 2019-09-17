// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#include <dirent.h>
#include <sys/stat.h>

#include <iostream>
#include <string>
#include <map>

#include "../include/walkfire/global.h"
#include "../include/walkfire/cmdline.h"
#include "../include/walkfire/downloader.h"

using std::cin;
using std::cout;
using std::string;
using std::map;


// 解析命令行参数
std::map<string, string> ParseCmd(int argc, char *argv[]) {
  cmdline::parser parser;
  parser.add<string>("url", 'u', "指定下载地址", true);
  parser.add<string>("dir", 'd', "指定工作目录", false, "wfire");
  parser.parse_check(argc, argv);

  std::map<string, string> parameters;
  parameters["url"] = parser.get<string>("url");
  parameters["dir"] = parser.get<string>("dir");
  return parameters;
}


// 判断工作目录是否存在
// 若不存在则新建工作目录
void CheckDir(string dir) {
  DIR *directory = NULL;
  directory = opendir(dir.c_str());
  if(directory == NULL)
    mkdir(dir.c_str(), S_IRWXU);
}


int main(int argc, char *argv[]) {
  map<string, string> parameters = ParseCmd(argc, argv);
  
  // 检查工作目录
  wfire::WORKSPACE = parameters["dir"];
  CheckDir(wfire::WORKSPACE);
  
  string url = parameters["url"];
  

  return 0;
}
