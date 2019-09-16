// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#include <curl/curl.h>
#include "../include/walkfire/urlparser.h"

using std::string;
using wfire::UrlParser;

UrlParser::UrlParser(string url) {
  url_ = url;
}

