// 

#include <curl/curl.h>
#include "../include/walkfire/urlparser.h"

using std::string;
using wfire::UrlParser;

UrlParser::UrlParser(string url) {
  url_ = url;
}

