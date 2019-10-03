// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 定义了流媒体片段信息类

#include "fragment.h"

namespace wfire {

TS::TS(string url, double extinf) {
  url_ = url;
  extinf_ = extinf;
}

TS::~TS() {}

void TS::set_filepath(string filepath) {
  filepath_ = filepath;
}

void TS::set_download_duration(double download_duration) {
  download_duration_ = download_duration;
}

void TS::set_isdownload(bool isdownload) {
  isdownload_ = isdownload;
}

string TS::url() const {
  return url_;
}

string TS::filepath() const {
  return filepath_;
}

double TS::extinf() const {
  return extinf_;
}

bool TS::isdownload() const {
  return isdownload_;
}

double TS::download_duration() const {
  return download_duration_;
}

}  // namespace wfire
