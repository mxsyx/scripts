// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC 3 许可证控制

#ifndef WFIRE_DOWNLOADER_H_
#define WFIRE_DOWNLOADER_H_

#include <iostream>
#include <string>

namespace wfire{

class Downloader{
private:
  /* data */
public:
  Downloader(/* args */);
  ~Downloader();

  void DownloadM3U8(std::string url);

  size_t WriteData(void *ptr, size_t size, size_t nmemb, void *fp);

};

} // namespace wfire

#endif
