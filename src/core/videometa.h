// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 定义了流媒体的源信息类

#ifndef WALKFIRE_CORE_VIDEOMETA_H_
#define WALKFIRE_CORE_VIDEOMETA_H_

#include <string>
#include <vector>
#include <map>

using std::string;

namespace wfire {

// 封装流媒体片段的源信息
// 一个流媒体片段即是一个.ts文件
class TS {
private:
  string url_;  // 流媒体片段地址
  string filepath_;  // 流媒体片段存储路径
  double extinf_ = 0.0;  // 流媒体片段时长
  double download_duration_ = 0.0;
  bool isdownload_ = false;

public:
  TS(string url, double extinf);
  ~TS();

  void set_filepath(string filepath);

  // 设置流媒体片段的下载历时
  void set_download_duration(double download_duration);

  // 设置流媒体片段是否下载完成
  void set_isdownload(bool isdownload);

  // 返回流媒体片段的地址
  string url() const;

  // 返回流媒体片段的存储路径
  string filepath() const;

  // 返回流媒体片段的时长
  double extinf() const;

  // 返回流媒体片段的下载历时
  double download_duration() const;

  // 返回流媒体片段是否下载完成
  bool isdownload() const;

};

// 封装流媒体备份源的源信息
class StreamInf {
private:
  string url_; // 备份源地址
  std::map<string, string> info_; // 备份源信息

public:
  StreamInf(string url);
  ~StreamInf();

  // 设置流媒体备份源的信息
  // 流媒体备份源通常包含一组键值对
  void set_info(string parameter, string value);
};

// 封装流媒体的相关信息
class VideoMeta {
private:
  int ext_x_version_ = 3;
  int ext_x_media_sequence_ = 0;
  double ext_x_targetduration_ = 0.0;
  std::vector<StreamInf> ext_x_stream_infs_;
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
    int ext_x_version();
    
    // 返回每个视频分段最大的时长
    double ext_x_targetduration();
    
    // 返回播放列表第一个流媒体片段的序列号
    int ext_x_media_sequence();

    // 返回某个流媒体片段的源信息对象
    // @param index 流媒体片段列表的索引
    TS& Tses(int index);

    // 返回流媒体片段列表的长度
    int TsNums();
};

}  // namespace wfire

#endif  // WALKFIRE_CORE_VIDEOMETA_H_
