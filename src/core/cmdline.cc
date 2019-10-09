// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 命令行参数解析器

#include "cmdline.h"

namespace wfspace {

// 解析命令行参数
std::map<std::string, std::string> ParseCmd(int argc, char *argv[]) {
  cmdline::parser parser;
  std::map<std::string, std::string> parameters;
  
  parser.add<std::string>("url",       'u', "指定下载地址", true);
  parser.add<std::string>("filename",  'f', "指定输出的文件名", true);
  parser.add<std::string>("threads",   't', "指定线程数量", false, "12");
  parser.add<std::string>("workspace", 'w', "指定工作目录", false, "wfspace");
  
  parser.parse_check(argc, argv);

  parameters["url"] = parser.get<std::string>("url");
  parameters["filename"] = parser.get<std::string>("filename");
  parameters["threads"] = parser.get<std::string>("threads");
  parameters["workspace"] = parser.get<std::string>("workspace");

  return parameters;
}

}  // namespace wfspace
