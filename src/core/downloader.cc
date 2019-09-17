// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#include "downloader.h"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include "global.h"

namespace wfire {

using std::string;

Downloader::Downloader(string url_) {
  url = url_;
}

void Downloader::Download() {
  DownloadM3U8(url);
}

void Downloader::DownloadM3U8(string url) {
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *curl = curl_easy_init();
  
  string filename = wfire::WORKSPACE + "/index.m3u8";
  FILE *fp = fopen(filename.c_str(), "w");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
}

string Downloader::MakeFilename() {
    std::chrono::milliseconds ms = 
    std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    std::stringstream ss;
    ss << ms.count();
    return ss.str();
}

int Downloader::WriteData(void *ptr, size_t size, size_t nmemb, void *fp) {
  int written = fwrite(ptr, size, nmemb, (FILE *)fp);
  return written;
}

}  // namespace wfire
