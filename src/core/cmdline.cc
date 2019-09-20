// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 命令行解析器

#include "cmdline.h"

using std::string;

namespace wfire {

// 解析命令行参数
std::map<string, string> ParseCmd(int argc, char *argv[]) {
  cmdline::parser parser;
  parser.add<std::string>("url", 'u', "指定下载地址", true);
  parser.add<std::string>("dir", 'd', "指定工作目录", false, "wfspace");
  parser.add<std::string>("filename", 'f', "指定输出的文件名", true);
  parser.parse_check(argc, argv);

  std::map<string, string> parameters;
  parameters["url"] = parser.get<string>("url");
  parameters["dir"] = parser.get<string>("dir");
  parameters["filename"] = parser.get<string>("filename");
  return parameters;
}

}  // namespace wfire
