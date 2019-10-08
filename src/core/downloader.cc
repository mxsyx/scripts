// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#include "downloader.h"
#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <thread>

using std::string;

namespace wfspace {

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

void Download(int start, int end, VideoMeta videometa) {  
  std::cout << "线程开始：(" << start << " " << end << + ")" << std::endl;

  CURL *curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Downloader::WriteData);

  for(int i = start; i < end; i++) {
    TS &ts = videometa.Tses(i);
    FILE *fp = fopen(ts.filepath().c_str(), "w");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_URL, ts.url().c_str());
    curl_easy_perform(curl);
    fclose(fp);
    std::cout << "片段已保存到：" << ts.filepath().c_str() << std::endl;
  }

  curl_easy_cleanup(curl);
}

void Downloader::DownloadTS(int threads, VideoMeta &videometa) {
  int start = 0, end = 0;
  int ts_nums = videometa.GetTsNumber();
  int each_nums = ts_nums / threads;
  std::vector<std::thread> tasks;
  curl_global_init(CURL_GLOBAL_ALL);
  for(int i = 0; i < threads; i++) {
    start = i * each_nums;
    end = (i + 1) * each_nums;
    end = end > ts_nums ? ts_nums : end;
    std::thread thread(Download, start, end, videometa);
    //tasks.push_back(std::thread();
  }
  for(int i = 0; i < threads; i++)
    tasks[i].join();
  curl_global_cleanup();
}

}  // namespace wfspace
