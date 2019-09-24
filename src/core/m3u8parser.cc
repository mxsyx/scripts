// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// M3U8文件内容解析器

#include "m3u8parser.h"
#include <regex>
#include <fstream>
#include <iostream>

using std::string;

namespace wfire {

M3U8Parser::M3U8Parser() {}

M3U8Parser::~M3U8Parser() {}

string M3U8Parser::ReadM3U8File(const string &filepath) {
  std::ifstream fin(filepath);
  if(fin) {
    fin.seekg(0, fin.end);
    const int buffer_length = fin.tellg();
    fin.seekg(0, fin.beg);
    char buffer[buffer_length];
    fin.read(buffer, buffer_length);
    fin.close();
    string rgx_string(buffer, buffer_length);
    return rgx_string;
  } else {
    return "";
  }
}

bool M3U8Parser::IsM3U8(const string &rgx_string) {
  std::regex rgx("#EXTM3U");
  std::smatch search_result;
  std::regex_search(rgx_string, search_result, rgx);
  if(search_result.size()) {
    return true;
  } else {
    return false;
  }
}

bool M3U8Parser::IsStreamInf(const string &filepath) {
  string rgx_string(ReadM3U8File(filepath));
  if(IsM3U8(rgx_string)) {
    std::regex rgx("#EXT-X-STREAM-INF.*");
    std::smatch search_result;
    std::regex_search(rgx_string, search_result, rgx);
    if(search_result.size()) {
      return true;
    } else {
      return false;
    }
  } else {
    std::cout << "不是M3U8文件, 程序退出！";
    exit(0);
  }
}

} // namespace wfire
