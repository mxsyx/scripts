// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 主调度模块

#include "walkfire.h"
#include <vector>
#include <chrono>
#include <sstream>
#include <iostream>
#include "combine.h"

using std::string;
using std::vector;

namespace wfspace {

string WalkFire::MakeFilename(const string &suffix) {
  static int64_t increment = 1;
  std::chrono::milliseconds ms = 
  std::chrono::duration_cast< std::chrono::milliseconds >(
      std::chrono::system_clock::now().time_since_epoch()
  );
  std::stringstream ss;
  ss << (ms.count() + increment++);
  string filename = ss.str() + suffix;
  return filename;
}

vector<string> WalkFire::MakeFilepath(const string &path, string suffix, int number) {
  vector<string> filepaths;
  for(int i = 0; i < number; i++)
    filepaths.push_back(path + MakeFilename(suffix));
  return filepaths;
}

string WalkFire::SpliceUrl(string url1, string url2) {
  int index = url1.find_last_of('/');
  url1.erase(index + 1, url1.size() - index);
  url1.append(url2);
  return url1;
}

void WalkFire::MakeAbsoluteUrl(vector<string> &ts_urls) {
  int ts_nums = ts_urls.size();
  const string starturl = global_.starturl();
  for(int i = 0; i < ts_nums; i++)
    ts_urls[i] = SpliceUrl(starturl, ts_urls[i]);
}

void WalkFire::SetExtXVersion() {
  int ext_x_version = m3u8parser_.ExtractExtXVersion();
  videometa_.set_ext_x_version(ext_x_version);
}

void WalkFire::SetExtXMediaSequence() {
  int ext_x_media_sequence = m3u8parser_.ExtractExtXMediaSequence();
  videometa_.set_ext_x_media_sequence(ext_x_media_sequence);
}

void WalkFire::SetExtXTargetDuration() {
  double ext_x_targetduration = m3u8parser_.ExtractExtXTargetDuration();
  videometa_.set_ext_x_targetduration(ext_x_targetduration);
}

void WalkFire::AppendTS() {
  vector<string> ts_urls = m3u8parser_.ExtractTSUrls();
  vector<double> extinfs = m3u8parser_.ExtractExtInfs();

  int ts_nums = ts_urls.size();

  // 生成TS文件的存储路径
  vector<string> filepaths = MakeFilepath(global_.cache_path_ts(), 
                                          ".ts", ts_nums);
  // 生成TS文件的绝对地址
  MakeAbsoluteUrl(ts_urls);

  // 追加TS到列表中
  for(int i = 0; i < ts_nums; i++)
    videometa_.AppendTS(ts_urls[i], extinfs[i], filepaths[i]);
}

void WalkFire::DownloadM3U8() {
  string filepath;  // 下载的M3U8文件存储路径
  string next_url = global_.starturl();
  while(!next_url.empty()) {
    filepath = global_.cache_path_m3u8() + MakeFilename(".m3u8");
    global_.set_m3u8_filepath(filepath);
    downloader_.DownloadM3U8(next_url, filepath);
    m3u8parser_.ChangeRgxString(filepath);
    if(m3u8parser_.IsStreamInf()) {
      std::cout << "是的";
      next_url = SpliceUrl(next_url, m3u8parser_.ExtractBackupUrl());
      global_.set_starturl(next_url);
    } else {
      return ;
    }
  }
}

void WalkFire::DownloadTS() {
  downloader_.DownloadTS(global_.threads(), videometa_);
}

void WalkFire::SetVideoMeta() {
  string m3u8_filepath = global_.m3u8_filepath();
  m3u8parser_.ChangeRgxString(m3u8_filepath);
  SetExtXVersion();
  SetExtXMediaSequence();
  SetExtXTargetDuration();
  AppendTS();
}

void WalkFire::CombineVideo() {
  vector<string> ts_paths;
  int ts_nums = videometa_.GetTsNumber();
  for(int i = 0; i < ts_nums; i++) {
    TS &ts = videometa_.Tses(i);
    ts_paths.push_back(ts.filepath());
  }
  Combine combine(global_.filename(), ts_paths);
  combine.CombineVideo("mp4");
}

WalkFire::WalkFire(Global &global):global_(global) {}

WalkFire::~WalkFire() {}

void WalkFire::Start() {
  DownloadM3U8();
  SetVideoMeta();
  DownloadTS();
  CombineVideo();
}

}  // namespce wfspace
