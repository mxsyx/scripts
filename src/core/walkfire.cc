// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 作者：江南的茶叶有甜 (zsimline@163.com)

#include "walkfire.h"
#include "common.h"
#include "cmdline.h"
#include <vector>

using std::string;
using std::vector;

namespace wfire {

string DownloadM3U8(string next_url, const string &cache_path_m3u8) {
  string filepath;  // 下载的M3U8文件存储路径
  while(!next_url.empty()) {
    filepath = cache_path_m3u8 + utils::MakeFilename(".m3u8");
    downloader.DownloadM3U8(next_url, filepath);
    m3u8parser.ChangeRgxString(filepath);
    next_url = (m3u8parser.IsStreamInf() ? utils::SpliceUrl(next_url,
                                m3u8parser.ExtractBackupUrl()) : "");
  }
  return filepath;
}

void SetExtXVersion() {
  int ext_x_version = m3u8parser.ExtractExtXVersion();
  videometa.set_ext_x_version(ext_x_version);
}

void SetExtXMediaSequence() {
  int ext_x_media_sequence = m3u8parser.ExtractExtXMediaSequence();
  videometa.set_ext_x_media_sequence(ext_x_media_sequence);
}

void SetExtXTargetDuration() {
  double ext_x_targetduration = m3u8parser.ExtractExtXTargetDuration();
  videometa.set_ext_x_targetduration(ext_x_targetduration);
}

void AppendTS() {
  vector<string> ts_urls = m3u8parser.ExtractTSUrls();
  vector<double> extinfs = m3u8parser.ExtractExtInfs();
  const int ts_nums = ts_urls.size();
  for(int i = 0; i < ts_nums; i++)
    videometa.AppendTS(ts_urls[i], extinfs[i]);
}

void SetVideoMeta(const string &m3u8_filepath) {
  m3u8parser.ChangeRgxString(m3u8_filepath);
  SetExtXVersion();
  SetExtXMediaSequence();
  SetExtXTargetDuration();
  AppendTS();
}

void DownloadTS(const string &cache_path_ts) {
  const int ts_nums = videometa.TsNums();
  string filepath;
  for(int index = 0; index < ts_nums; index++) {
    TS& ts = videometa.Tses(index);
    filepath = cache_path_ts + utils::MakeFilename(".ts");
    downloader.DownloadTS("https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/" + ts.url(), filepath);
  }
}

}  // namespce wfire


int main(int argc, char *argv[]) {
  // 解析命令行参数
  std::map<string, string> parameters(wfire::ParseCmd(argc, argv));

  // 起始地址
  const string start_url(parameters["url"]);
  // 输出的文件名
  const string filename(parameters["filename"]);
  // 程序工作目录
  const string workspace(parameters["workspace"] + "/");


  // 缓存文件根目录
  const string cache_path(workspace + "cache/");
  // M3U8文件缓存目录
  const string cache_path_m3u8(cache_path + "m3u8/");
  // TS文件缓存目录
  const string cache_path_ts(cache_path + "ts/");
  
  // 检查工作目录是否存在
  wfire::utils::CheckDir(workspace);
  wfire::utils::CheckDir(cache_path);
  wfire::utils::CheckDir(cache_path_m3u8);
  wfire::utils::CheckDir(cache_path_ts);

  const string m3u8_filepath(wfire::DownloadM3U8(start_url, cache_path_m3u8));
  wfire::SetVideoMeta(m3u8_filepath);
  wfire::DownloadTS(cache_path_ts);
  return 0;
}
