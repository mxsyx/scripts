//

#ifndef WFIRE_META_H_
#define WFIRE_MATE_H_

#include <string>
#include <vector>
#include <stack>
#include <map>

namespace wfire {

using std::string;


// 存储流媒体片段的相关信息
class Stream {
private:
  string url_ = NULL;    // 流媒体片段地址
  double extinf_ = 0.0;  // 流媒体片段时长
  double download_duration_ = 0.0;
  bool isdownload_ = false;

public:
  Stream(string url, double extinf);
  ~Stream();

  // 设置流媒体片段的下载历时
  void set_download_duration(double download_duration);
  
  // 设置流媒体片段是否下载完成
  void set_isdownload(bool isdownload);

  // 返回流媒体片段的下载历时
  double download_duration();

  // 返回流媒体片段是否下载完成
  bool isdownload();

};

// 存储流媒体备份源的相关信息
class StreamInf {
private:
  string url_ = ""; // 备份源地址
  std::map<string, string> info_; // 备份源信息
public:
  StreamInf(string url_);
  ~StreamInf();

  // 设置存储流媒体备份源的信息
  void set_info(string parameter, string value);
};


class Meta {
private:
  int ext_x_version_ = 3;
  int ext_x_media_sequence_ = 0;
  double ext_x_targetduration_ = 0.0;
  std::stack<StreamInf> ext_x_stream_inf;
  std::vector<Stream> streams_;

public:
    Meta();
    ~Meta();

    // 设置M3U8文件的版本（一般为3）
    void set_ext_x_version(int ext_x_version);
    
    // 设置播放列表第一个流媒体片段的序列号（默认为0）
    void set_ext_x_media_sequence(int ext_x_media_sequence);

    // 设置每个视频分段最大的时长（单位为秒）
    void set_ext_x_targetduration(double ext_x_targetduration);

    // 返回M3U8文件的版本
    int ext_x_version();
    
    // 返回每个视频分段最大的时长
    double ext_x_targetduration();
    
    // 返回播放列表第一个流媒体片段的序列号
    int ext_x_media_sequence();

    // 向任务流媒体列表追加一个流
    void append_stream(string url, double extinf);
};

}

#endif
