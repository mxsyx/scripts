// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// M3U8文件内容解析器

#include "m3u8parser.h"
#include <regex>
#include <fstream>
#include <iostream>
#include <vector>

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

string M3U8Parser::ExtractBackupUrl(const string &filepath) {
  string rgx_string(ReadM3U8File(filepath));
  std::regex rgx("[^\n#].*\\.m3u8");
  std::smatch search_result;
  std::regex_search(rgx_string, search_result, rgx);
  if(search_result.size()) {
    return search_result[0];
  } else {
    return "";
  }
}

void M3U8Parser::ParserM3U8(const string &filepath) {
  string rgx_string(ReadM3U8File(filepath));
  std::vector<string> fragment_urls;
  if(IsM3U8(rgx_string)) {
    std::regex rgx(".*\\.ts");
    std::smatch search_result;
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> rgx_iterator(
                        rgx_string.begin(), rgx_string.end(), rgx);
    while(rgx_iterator != rend)
      fragment_urls.push_back(*rgx_iterator++);
  }
}

} // namespace wfire
