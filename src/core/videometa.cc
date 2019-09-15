// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC 3 许可证控制

#include "../include/walkfire/videometa.h"

using std::string;
using std::vector;
using wfire::Fragment;
using wfire::StreamInf;
using wfire::VideoMeta;


// Fragment 类方法定义
Fragment::Fragment(string url, double extinf) {
  url_ = url;
  extinf_ = extinf;
}

void Fragment::set_download_duration(double download_duration) {
  download_duration_ = download_duration;
}

void Fragment::set_isdownload(bool isdownload) {
  isdownload_ = isdownload;
}

bool Fragment::isdownload() {
  return isdownload_;
}

double Fragment::download_duration() {
  return download_duration_;
}


// StreamInf 类方法定义
StreamInf::StreamInf(string url) {
  url_ = url;
}

StreamInf::set_info(string parameter, string value) {
  info_[parameter] = value;
}


// VideoMeta 类方法定义
void VideoMeta::set_ext_x_version(int ext_x_version) {
  ext_x_version_ = ext_x_version;
}

void VideoMeta::set_ext_x_targetduration(double ext_x_targetduration) {
  ext_x_targetduration_ = ext_x_targetduration;
}

void VideoMeta::set_ext_x_media_sequence(int ext_x_media_sequence) {
  ext_x_media_sequence_ = ext_x_media_sequence;
}

int VideoMeta::ext_x_version() {
  return ext_x_version_;
}

double VideoMeta::ext_x_targetduration() {
  return ext_x_targetduration_;
}

int VideoMeta::ext_x_media_sequence() {
  return ext_x_media_sequence_;
}

void VideoMeta::append_fragment(string url, double extinf) {
  Fragment fragment(url, extinf);
  fragments_.push_back(fragment);
}

