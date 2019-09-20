// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// M3U8文件内容解析器

#ifndef WALKFIRE_CORE_URLPARSER_H_
#define WALKFIRE_CORE_URLPARSER_H_

#include <regex>
#include <string>

namespace wfire {

using std::string;

class M3U8Parser{
private:
  string filename_ = NULL;

public:
  M3U8Parser(string filename);
  ~M3U8Parser();

  // 解析M3U8文件
  void Parser();

  bool IsM3U8();
};

}  // namespace wfire

#endif  // WALKFIRE_CORE_URLPARSER_H_
