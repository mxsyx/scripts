//

#ifndef WFIRE_URLPARSER_H_
#define WFIRE_URLPARSER_H_

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