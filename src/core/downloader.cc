// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#include "downloader.h"
#include <iostream>
#include <vector>
#include <thread>

using std::string;

namespace wfspace {

Downloader::Downloader() {
  CurlGlobalInit();
}

Downloader::~Downloader() {
  CurlGlobalCleanup();
}

int Downloader::WriteData(const void *buffer, size_t size, 
                          size_t count, void *stream) {
  int written = fwrite(buffer, size, count, (FILE *)stream);
  return written;
}

void Downloader::CurlGlobalCleanup() {
  curl_global_init(CURL_GLOBAL_ALL);
}

void Downloader::CurlGlobalInit() {
  curl_global_cleanup();
}

void Downloader::CurlEasySetopt(CURL *curl, const string &url, 
                                const FILE *stream) {
  // 设置下载地址
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  // 设置下载完成后的回调函数
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Downloader::WriteData);
  // 设置文件写入指针
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
}

string Downloader::DownloadM3U8(const string &url,
                                const string &filepath) {
  CURL *curl = curl_easy_init();
  FILE *stream = fopen(filepath.c_str(), "w");
  
  CurlEasySetopt(curl, url, stream);
  curl_easy_perform(curl);

  fclose(stream);
  curl_easy_cleanup(curl);

  return filepath;
}

void Downloader::Download(int thread_id, int start, int end, VideoMeta &videometa) {
  CURL *curl = curl_easy_init();
  
  for(int i = start; i < end; i++) {
    TS &ts = videometa.Tses(i);
    FILE *stream = fopen(ts.filepath().c_str(), "w");

    CurlEasySetopt(curl, ts.url().c_str(), stream);
    curl_easy_perform(curl);
    ts.set_isdownload(true);

    std::cout << "线程 " << thread_id << " 剩余 " << end - i << std::endl;
    fclose(stream);
  }

  curl_easy_cleanup(curl);
  return ;
}

void Downloader::DownloadTS(int threads, VideoMeta &videometa) {
  int start = 0, end = 0;
  int ts_nums = videometa.GetTsNumber();
  // 每个线程的任务数
  int each_nums = (ts_nums + threads) / threads;
  std::vector<std::thread> tasks;
  for(int i = 0; i < threads; i++) {
    start = i * each_nums;
    end = (i + 1) * each_nums;
    end = end > ts_nums ? ts_nums : end;
    std::thread thread(&Downloader::Download, this, i, start, end, std::ref(videometa));
    tasks.push_back(std::move(thread));
  }
  for(int i = 0; i < threads; i++) {
    tasks[i].join();
  }
  std::cout << std::endl << "下载完成！！！" << std::endl;
}

}  // namespace wfspace
