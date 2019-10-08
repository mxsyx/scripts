// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 定义了视频源信息类

#include "videometa.h"

using std::string;

namespace wfspace {

VideoMeta::VideoMeta() {}

VideoMeta::~VideoMeta() {}

void VideoMeta::set_ext_x_version(int ext_x_version) {
  ext_x_version_ = ext_x_version;
}

void VideoMeta::set_ext_x_media_sequence(int ext_x_media_sequence) {
  ext_x_media_sequence_ = ext_x_media_sequence;
}

void VideoMeta::set_ext_x_targetduration(double ext_x_targetduration) {
  ext_x_targetduration_ = ext_x_targetduration;
}

void VideoMeta::AppendStreamInf(string url) {
  ext_x_stream_infs_.push_back(url);
}

void VideoMeta::AppendTS(string url, double extinf, string filepath) {
  TS ts(url, extinf, filepath);
  tses_.push_back(ts);
}

int VideoMeta::ext_x_version() const {
  return ext_x_version_;
}

double VideoMeta::ext_x_targetduration() const {
  return ext_x_targetduration_;
}

int VideoMeta::ext_x_media_sequence() const {
  return ext_x_media_sequence_;
}

int VideoMeta::GetTsNumber() const {
  return tses_.size();
}

TS& VideoMeta::Tses(int index) {
  return tses_[index];
}

}  // namespace wfspace
