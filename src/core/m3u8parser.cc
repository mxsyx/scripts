// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// M3U8文件内容解析器

#include "m3u8parser.h"
#include <fstream>
#include <iostream>
#include <boost/regex.hpp>

#define RGX_EXTM3U               "#EXTM3U"
#define RGX_EXT_X_VERSION        "(?<=#EXT-X-VERSION:)\\d+"
#define RGX_TSURLS               "(?<=\n)[^#].*?(?=\n)"
#define RGX_EXTINFS              "(?<=#EXTINF:)\\d+\\.\\d+"
#define RGX_EXT_X_STREAM_INF     "#EXT-X-STREAM-INF.*"
#define RGX_BACKUPURL            "(?<=\n)[^#].*"
#define RGX_EXT_X_MEDIA_SEQUENCE "(?<=EXT-X-MEDIA-SEQUENCE:)\\d+"
#define RGX_EXT_X_TARGETDURATION "(?<=EXT-X-TARGETDURATION:)\\d+"

using std::string;
using std::vector;

namespace wfspace {

M3U8Parser::M3U8Parser() {}

M3U8Parser::~M3U8Parser() {}

string M3U8Parser::ReadM3U8File(const string &filepath) {
  std::ifstream fin(filepath);
  if(fin) {
    fin.seekg(0, fin.end);
    const int buffer_length = fin.tellg();
    char buffer[buffer_length];
    fin.seekg(0, fin.beg);
    fin.read(buffer, buffer_length);
    fin.close();
    string rgx_string(buffer, buffer_length);
    return rgx_string;
  } else {
    return "";
  }
}

bool M3U8Parser::IsM3U8() const {
  boost::regex rgx(RGX_EXTM3U);
  boost::smatch search_result;
  boost::regex_search(rgx_string_, search_result, rgx);
  if(search_result.size()) {
    return true;
  } else {
    return false;
  }
}

void M3U8Parser::ChangeRgxString(const string &filepath) {
  rgx_string_ = ReadM3U8File(filepath);
}

bool M3U8Parser::IsStreamInf() const {
  if(IsM3U8()) {
    boost::regex rgx(RGX_EXT_X_STREAM_INF);
    boost::smatch search_result;
    boost::regex_search(rgx_string_, search_result, rgx);
    if(search_result.size()) {
      return search_result[0].str().empty() ? false : true;
    } else {
      return false;
    }
  } else {
    std::cout << "不是M3U8文件, 程序退出！";
    exit(0);
  }
}

string M3U8Parser::ExtractBackupUrl() const{
  boost::regex rgx(RGX_BACKUPURL);
  boost::smatch search_result;
  boost::regex_search(rgx_string_, search_result, rgx);
  if(search_result.size()) {
    return search_result[0].str();
  } else {
    return "";
  }
}

int M3U8Parser::ExtractExtXVersion() const {
  boost::regex rgx(RGX_EXT_X_VERSION);
  boost::smatch search_result;
  boost::regex_search(rgx_string_, search_result, rgx);
  return stoi(search_result[0].str());
}

vector<string> M3U8Parser::ExtractTSUrls() const {
  std::vector<string> ts_urls;
  boost::regex rgx(RGX_TSURLS);
  boost::smatch search_result;
  boost::regex_token_iterator<string::const_iterator> rend;
  boost::regex_token_iterator<string::const_iterator> rgx_iterator(
                       rgx_string_.begin(), rgx_string_.end(), rgx);
  while(rgx_iterator != rend) {
    ts_urls.push_back((*rgx_iterator).str());
    rgx_iterator++;
  }
  return ts_urls;
}

vector<double> M3U8Parser::ExtractExtInfs() const {
  std::vector<double> extinfs;
  boost::regex rgx(RGX_EXTINFS);
  boost::smatch search_result;
  boost::regex_token_iterator<string::const_iterator> rend;
  boost::regex_token_iterator<string::const_iterator> rgx_iterator(
                       rgx_string_.begin(), rgx_string_.end(), rgx);
  while(rgx_iterator != rend) {
    extinfs.push_back(stod((*rgx_iterator).str()));
    rgx_iterator++;
  }
  return extinfs;
}

int M3U8Parser::ExtractExtXMediaSequence() const {
  boost::regex rgx(RGX_EXT_X_MEDIA_SEQUENCE);
  boost::smatch search_result;
  boost::regex_search(rgx_string_, search_result, rgx);
  return stoi(search_result[0].str());
}

int M3U8Parser::ExtractExtXTargetDuration() const {
  boost::regex rgx(RGX_EXT_X_TARGETDURATION);
  boost::smatch search_result;
  boost::regex_search(rgx_string_, search_result, rgx);
  return stoi(search_result[0].str());
}

} // namespace wfspace
