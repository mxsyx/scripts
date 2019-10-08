// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 多线程下载器

#ifndef WALKFIRE_CORE_DOWNLOADER_H_
#define WALKFIRE_CORE_DOWNLOADER_H_

#include <string>
#include "videometa.h"

using std::string;

namespace wfspace{
void Download(int start, int end, VideoMeta videometa);

class Downloader {
private:
  // 文件内容写入
public:
  Downloader();
  ~Downloader();
  static int WriteData(void *ptr, size_t size, size_t nmemb, void *fp);
  
  // 下载流媒体文件
  // @param url TS文件的链接
  // @param filepath TS文件的存储路径
  void DownloadTS(int threads, VideoMeta &videometa);
  
  // 下载M3U8索引文件
  // @param url M3U8索引文件的链接
  // @param filepath M3U8索引文件的存储路径
  string DownloadM3U8(const string &url, const string &filepath);

};



}  // namespace wfspace

#endif  // WALKFIRE_CORE_DOWNLOADER_H_
