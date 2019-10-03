// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 主调度模块

#include "master.h"
#include "common.h"

#include <vector>
#include <chrono>
#include <sstream>

using std::string;
using std::vector;

namespace wfire {

string Master::MakeFilename(string suffix) {
  std::chrono::milliseconds ms = 
  std::chrono::duration_cast< std::chrono::milliseconds >(
      std::chrono::system_clock::now().time_since_epoch()
  );
  std::stringstream ss;
  ss << ms.count();
  return ss.str() + suffix;
}

string Master::SpliceUrl(string url1, string url2) {
  int index = url1.find_last_of('/');
  url1.erase(index + 1, url1.size() - index);
  url1.append(url2);
  return url1;
}

void Master::SetExtXVersion() {
  int ext_x_version = m3u8parser_.ExtractExtXVersion();
  videometa_.set_ext_x_version(ext_x_version);
}

void Master::SetExtXMediaSequence() {
  int ext_x_media_sequence = m3u8parser_.ExtractExtXMediaSequence();
  videometa_.set_ext_x_media_sequence(ext_x_media_sequence);
}

void Master::SetExtXTargetDuration() {
  double ext_x_targetduration = m3u8parser_.ExtractExtXTargetDuration();
  videometa_.set_ext_x_targetduration(ext_x_targetduration);
}

void Master::AppendTS() {
  vector<string> ts_urls = m3u8parser_.ExtractTSUrls();
  vector<double> extinfs = m3u8parser_.ExtractExtInfs();
  const int ts_nums = ts_urls.size();
  for(int i = 0; i < ts_nums; i++)
    videometa_.AppendTS(ts_urls[i], extinfs[i]);
}

string Master::DownloadM3U8(string next_url, const string &cache_path_m3u8) {
  string filepath;  // 下载的M3U8文件存储路径
  while(!next_url.empty()) {
    filepath = cache_path_m3u8 + MakeFilename(".m3u8");
    downloader_.DownloadM3U8(next_url, filepath);
    m3u8parser_.ChangeRgxString(filepath);
    next_url = (m3u8parser_.IsStreamInf() ? SpliceUrl(next_url,
                                m3u8parser_.ExtractBackupUrl()) : "");
  }
  return filepath;
}

void Master::DownloadTS(const string &cache_path_ts) {
  const int ts_nums = videometa_.GetTsNumber();
  string filepath;
  for(int index = 0; index < ts_nums; index++) {
    TS& ts = videometa_.Tses(index);
    filepath = cache_path_ts + MakeFilename(".ts");
    downloader_.DownloadTS("https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/" + ts.url(), filepath);
  }
}

void Master::SetVideoMeta(const string &m3u8_filepath) {
  m3u8parser_.ChangeRgxString(m3u8_filepath);
  SetExtXVersion();
  SetExtXMediaSequence();
  SetExtXTargetDuration();
  AppendTS();
}

}  // namespce wfire
