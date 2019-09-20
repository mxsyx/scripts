// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 多线程下载器

#ifndef WALKFIRE_CORE_DOWNLOADER_H_
#define WALKFIRE_CORE_DOWNLOADER_H_

#include <string>

using std::string;

namespace wfire{

class Downloader {
private:
  static int WriteData(void *ptr, size_t size, size_t nmemb, void *fp);
public:
  Downloader();
  ~Downloader();
  
  // 下载流媒体文件
  void DownloadTS(string url, string dir);
  
  // 下载M3U8索引文件
  void DownloadM3U8(string url, string dir);

};

}  // namespace wfire

#endif  // WALKFIRE_CORE_DOWNLOADER_H_
