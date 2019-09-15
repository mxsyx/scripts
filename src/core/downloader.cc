// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC 3 许可证控

#include <stdio.h>
#include <curl/curl.h>
#include "../include/walkfire/downloader.h"

using std::string;
using wfire::Downloader;

extern string WORKSPACE;

int WriteData(void *ptr, size_t size, size_t nmemb, void *fp) {
  int written = fwrite(ptr, size, nmemb, (FILE *)fp);
  return written;
}

void Downloader::DownloadM3U8(string url) {
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *curl = curl_easy_init();
  
  string filename = WORKSPACE + "/index.m3u8";
  FILE *fp = fopen(filename.c_str(), "w");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
}
