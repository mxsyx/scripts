// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#include "downloader.h"
#include <curl/curl.h>
#include <iostream>
#include <thread>

using std::string;

namespace wfire {

Downloader::Downloader() {}

Downloader::~Downloader() {}

int Downloader::WriteData(void *ptr, size_t size, size_t nmemb, void *fp) {
  int written = fwrite(ptr, size, nmemb, (FILE *)fp);
  return written;
}

string Downloader::DownloadM3U8(const string &url, const string &filepath) {
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *curl = curl_easy_init();
  
  std::cout << std::endl << "[INFO]下载流媒体索引文件\n  - 地址为：" 
            << url << std::endl;
  FILE *fp = fopen(filepath.c_str(), "w");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Downloader::WriteData);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
  curl_easy_perform(curl);
  fclose(fp);
  std::cout << "  - 文件已保存到：" << filepath << std::endl;

  curl_easy_cleanup(curl);
  curl_global_cleanup();
  return filepath;
}

void Downloader::DownloadTS(const string &url, const string &filepath) {
  CURL *curl = curl_easy_init();
  FILE *fp = fopen(filepath.c_str(), "w");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Downloader::WriteData);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
  curl_easy_perform(curl);
  fclose(fp);
  std::cout << "片段已保存到：" << filepath << std::endl;
  curl_easy_cleanup(curl);
}

void Downloader::Download(VideoMeta& videometa) {
  curl_global_init(CURL_GLOBAL_ALL);
  std::vector<std::thread> tasks;
  const int task_number = videometa.GetTsNumber();
  for(int i = 0; i < task_number; i++) {
    std::thread task(&Downloader::DownloadTS, videometa.Tses(i).url(), "csac");
    tasks.push_back(task);
  }
  for(int i = 0; i < task_number; i++)
    tasks[i].join();
  curl_global_cleanup();
}

}  // namespace wfire
