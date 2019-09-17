// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#ifndef WALKFIRE_CORE_URLPARSER_H_
#define WALKFIRE_CORE_URLPARSER_H_

#include <regex>
#include <string>

namespace wfire {

using std::string;

class UrlParser{
private:
  string url_ = NULL;

public:
  UrlParser(string url);
  ~UrlParser();

  // 解析M3U8文件
  void Parser();

  bool IsM3u8();
};

} // namespace wfire

#endif