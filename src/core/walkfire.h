// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 主调度模块

#ifndef WALKFIRE_CORE_WALKFIRE_H_
#define WALKFIRE_CORE_WALKFIRE_H_

#include <vector>
#include "global.h"
#include "videometa.h"
#include "m3u8parser.h"
#include "downloader.h"

namespace wfspace {

// 主调度类
class WalkFire {
private:
  // 全局状态对象
  Global &global_;

  // 视频源信息对象
  VideoMeta videometa_;
  
  // M3U8文件解析器
  M3U8Parser m3u8parser_;
  
  // 多线程下载器
  Downloader downloader_;
  
  // 根据时间戳字符串生成文件名
  // @param suffix 文件名后缀
  string MakeFilename(const string &suffix);
  
  // 批量生成流媒体片段的存储路径
  // @param path   流媒体片段缓存目录
  // @param suffix 流媒体片段文件后缀
  // @param number 流媒体片段总的个数
  std::vector<string> MakeFilepath(const string &path, string suffix, int number);

  // 生成流媒体片段的绝对地址
  // @param ts_urls 流媒体片段的相对地址
  void MakeAbsoluteUrl(std::vector<string> &ts_urls);
  
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

  // 下载 M3U8 文件
  // 如果下载的文件不是最终包含TS文件链接的M3U8文件，
  // 而是指向了一个M3U8备份文件，则去下载这个备份文件
  void DownloadM3U8();

  // 下载 TS 文件
  // 调用下载器的中的多线程下载函数
  void DownloadTS();

  // 设置视频源信息
  // @param m3u8_filepath M3U8文件的存储路径
  void SetVideoMeta();

public:
  WalkFire(Global& global);
  ~WalkFire();

  // 主调度器入口函数
  void Start();
  
};

}  // namespace wfspace

#endif
