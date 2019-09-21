// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#include "m3u8parser.h"
#include <regex>
#include <fstream>

using std::string;

namespace wfire {

M3U8Parser::M3U8Parser() {}

M3U8Parser::~M3U8Parser() {}

string M3U8Parser::ReadM3U8File(string &filepath) {
  std::ifstream fin("example.txt");
  if (fin) {
    fin.seekg(0, fin.end);
    const int kLineLength = fin.tellg();
    char buffer[kLineLength];
    fin.getline(buffer, kLineLength);
    string rgx_string(buffer, kLineLength);
    return rgx_string;
  } else {
    return "";
  }
}

bool M3U8Parser::IsM3U8(string &filepath) {
  string rgx_string(ReadM3U8File(filepath));

  std::regex rgx("#EXT-X-STREAM-INF.*");
  std::smatch match_result;
  std::regex_match(rgx_string, match_result, rgx);
  if(match_result.size()) {
    return false;
  } else {
    return true;
  }
}

} // namespace wfire
