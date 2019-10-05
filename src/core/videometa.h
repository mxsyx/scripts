// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 定义了视频源信息类

#ifndef WALKFIRE_CORE_VIDEOMETA_H_
#define WALKFIRE_CORE_VIDEOMETA_H_

#include <string>
#include <vector>
#include "fragment.h"

using std::string;

namespace wfire {

// 封装流媒体的源信息
class VideoMeta {
private:
  int ext_x_version_ = 3;
  int ext_x_media_sequence_ = 0;
  double ext_x_targetduration_ = 0.0;
  std::vector<string> ext_x_stream_infs_;
  std::vector<TS> tses_;

public:
  VideoMeta();
  ~VideoMeta();

  // 设置M3U8文件的版本（一般为3）
  void set_ext_x_version(int ext_x_version);
    
  // 设置播放列表第一个流媒体片段的序列号（默认为0）
  void set_ext_x_media_sequence(int ext_x_media_sequence);

  // 设置每个视频分段最大的时长（单位为秒）
  void set_ext_x_targetduration(double ext_x_targetduration);

  // 向备份源列表追加一个备份源
  void AppendStreamInf(string url);
    
  // 向流媒体片段列表追加一个片段
  void AppendTS(string url, double extinf);

  // 返回M3U8文件的版本
  int ext_x_version() const;
    
  // 返回播放列表第一个流媒体片段的序列号
  int ext_x_media_sequence() const;
    
  // 返回每个视频分段最大的时长
  double ext_x_targetduration() const;

  // 返回流媒体片段列表的长度
  int GetTsNumber() const;

  // 返回某个流媒体片段的源信息对象
  // @param index 流媒体片段的索引
  TS& Tses(int index);

};

}  // namespace wfire

#endif  // WALKFIRE_CORE_VIDEOMETA_H_
