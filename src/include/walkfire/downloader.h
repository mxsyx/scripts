//

#ifndef WFIRE_DOWNLOADER_H_
#define WFIRE_DOWNLOADER_H_

#include<iostream>

namespace wfire{

class Downloader{
private:
  /* data */
public:
  Downloader(/* args */);
  ~Downloader();

  void download(string url);

  size_t WriteData(void *ptr, size_t size, size_t nmemb, void *fp);

};

} // namespace wfire

#endif