// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#ifndef WALKFIRE_CORE_DOWNLOADER_H_
#define WALKFIRE_CORE_DOWNLOADER_H_

#include <string>

namespace wfire{

using std::string;

class Downloader{
private:
  string url = NULL;
  void DownloadTS(string url);
  void DownloadM3U8(string url);
  int WriteData(void *ptr, size_t size, size_t nmemb, void *fp);
  string MakeFilename();
public:
  Downloader(string url_);
  ~Downloader();

  void Download();

};

}  // namespace wfire

#endif  // WALKFIRE_CORE_DOWNLOADER_H_
