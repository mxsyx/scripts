// Copyright (c) 2019

#include "../include/walkfire/videometa.h"

using std::string;
using std::vector;
using wfire::Meta;
using wfire::Stream;
using wfire::StreamInf;


// Stream 类方法定义
Stream::Stream(string url, double extinf) {
  url_ = url;
  extinf_ = extinf;
}

void Stream::set_download_duration(double download_duration) {
  download_duration_ = download_duration;
}

void Stream::set_isdownload(bool isdownload) {
  isdownload_ = isdownload;
}

bool Stream::isdownload() {
  return isdownload_;
}

double Stream::download_duration() {
  return download_duration_;
}


// StreamInf 类方法定义
StreamInf::StreamInf(string url) {
  url_ = url;
}

StreamInf::set_info(string parameter, string value){
  info_[parameter] = value;
}


// Meta 类方法定义
void Meta::set_ext_x_version(int ext_x_version) {
  ext_x_version_ = ext_x_version;
}

void Meta::set_ext_x_targetduration(double ext_x_targetduration) {
  ext_x_targetduration_ = ext_x_targetduration;
}

void Meta::set_ext_x_media_sequence(int ext_x_media_sequence) {
  ext_x_media_sequence_ = ext_x_media_sequence;
}

int Meta::ext_x_version()
{
  return ext_x_version_;
}

double Meta::ext_x_targetduration() {
  return ext_x_targetduration_;
}

int Meta::ext_x_media_sequence() {
  return ext_x_media_sequence_;
}


void Meta::append_stream(string url, double extinf) {
  Stream stream(url, extinf);
  streams_.push_back(stream);
}
