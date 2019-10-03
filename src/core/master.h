// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 主调度模块

#ifndef WALKFIRE_CORE_MASTER_H_
#define WALKFIRE_CORE_MASTER_H_

#include "videometa.h"
#include "m3u8parser.h"
#include "downloader.h"

namespace wfire {

// 主调度类
class Master {
private:
  // 视频源信息对象
  VideoMeta videometa_;  
  
  // M3U8文件解析器
  M3U8Parser m3u8parser_;
  
  // 多线程下载器
  Downloader downloader_;
  
  // 根据时间戳字符串生成文件名
  // @param suffix 文件名后缀
  string MakeFilename(string suffix);

  // 将两个URL拼接为一个URL
  string SpliceUrl(string url1, string url2);

  // 设置M3U8文件版本
  void SetExtXVersion();

  // 设置播放列表第一个流媒体片段的序列号
  void SetExtXMediaSequence();

  // 设置每个视频分段最大的时长
  void SetExtXTargetDuration();

  // 向备份源列表追加一个备份源
  void AppendStreamInf();
  
  // 向流媒体片段列表追加一个片段
  void AppendTS();

public:
  Master();
  ~Master();

  // 下载 M3U8 文件
  // 如果下载的文件不是最终包含TS文件链接的M3U8文件，
  // 而是指向了一个M3U8备份文件，则去下载这个备份文件
  // @param next_url 下一个将被下载的文件的链接
  // @param cache_path_m3u8 M3U8文件的缓存目录
  string DownloadM3U8(string next_url, const string &cache_path_m3u8);

  // 下载 TS 文件
  void DownloadTS(const string &cache_path_ts);

  // 设置视频源信息
  // @param m3u8_filepath M3U8文件的存储路径
  void SetVideoMeta(const string &m3u8_filepath);

};

}  // namespace wfire

#endif
