// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 定义了流媒体片段信息类

#ifndef WALKFIRE_CORE_FRAGMENT_H_
#define WALKFIRE_CORE_FRAGMENT_H_

#include <string>

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

}  // namespace wfire

#endif  // WALKFIRE_CORE_FRAGMENT_H_
