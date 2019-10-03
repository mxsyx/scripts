// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 定义了视频源信息类

#include "videometa.h"

using std::string;

namespace wfire {


// VideoMeta 类方法定义
VideoMeta::VideoMeta() {}

VideoMeta::~VideoMeta() {}

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

void VideoMeta::AppendStreamInf(string url) {
  StreamInf streaminf(url);
  ext_x_stream_infs_.push_back(streaminf);
}

void VideoMeta::AppendTS(string url, double extinf) {
  TS ts(url, extinf);
  tses_.push_back(ts);
}

TS& VideoMeta::Tses(int index) {
  return tses_[index];
}

int VideoMeta::TsNums() {
  return tses_.size();
}

}  // namespace wfire
