// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 多线程下载器

#ifndef WALKFIRE_CORE_DOWNLOADER_H_
#define WALKFIRE_CORE_DOWNLOADER_H_

#include <curl/curl.h>
#include <string>
#include "videometa.h"

using std::string;

namespace wfspace{

class Downloader {
private:
  // Curl全局初始化
  void CurlGlobalInit();

  // Curl全局清理
  void CurlGlobalCleanup();

  // 设置下载选项
  // @param curl Curl指针
  // @param url 下载地址
  // @param stream 文件指针
  void CurlEasySetopt(CURL *curl, const string &url, const FILE *stream);

public:
  Downloader();
  ~Downloader();

  // 文件内容写入
  // @param buffer 缓存区指针
  // @param size   每个块的大小
  // @param count  写入块的数量
  // @param stream 文件指针
  int static WriteData(const void *buffer, size_t size, 
                       size_t nmemb, void *stream);

  // 下载流媒体片段文件
  // @param start 起始的流媒体片段索引
  // @param end   终止的流媒体片段索引
  // @param videometa 视频源信息对象
  // 函数下载流媒体片段列表中处于start到end范围内的片段文
  void Download(int thread_i, int start, int end, VideoMeta &videometa);

  // 下载流媒体索引文件
  // @param url 流媒体索引文件的链接
  // @param filepath 流媒体索引文件的存储路径
  string DownloadM3U8(const string &url, const string &filepath);

  // 下载流媒体文件
  // @param threads 线程数量
  // @param videometa 视频源信息对象
  // 函数生成 threads 个线程，并为每个线程分配一定数量的任务
  void DownloadTS(int threads, VideoMeta &videometa);
};

}  // namespace wfspace

#endif  // WALKFIRE_CORE_DOWNLOADER_H_
