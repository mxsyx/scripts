// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 定义了流媒体片段信息类

#ifndef WALKFIRE_CORE_FRAGMENT_H_
#define WALKFIRE_CORE_FRAGMENT_H_

#include <string>

using std::string;

namespace wfspace {

// 封装流媒体片段的源信息
// 一个流媒体片段即是一个.ts文件
class TS {
private:
  string url_;  // 流媒体片段链接
  string filepath_;  // 流媒体片段存储路径
  double extinf_ = 0.0;  // 流媒体片段时长
  bool isdownload_ = false;

public:
  // 构造函数接受两个参数
  // @param url 流媒体片段的链接
  // @param extinf 流媒体片段时长
  TS(string url, double extinf, string filepath);
  ~TS();

  // 设置流媒体片段的存储路径
  void set_filepath(string filepath);

  // 设置流媒体片段是否下载完成
  void set_isdownload(bool isdownload);

  // 返回流媒体片段的地址
  string url() const;

  // 返回流媒体片段的存储路径
  string filepath() const;

  // 返回流媒体片段的时长
  double extinf() const;

  // 返回流媒体片段是否下载完成
  bool isdownload() const;
};

}  // namespace wfspace

#endif  // WALKFIRE_CORE_FRAGMENT_H_
