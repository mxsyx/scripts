// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 作者：江南的茶叶有甜 (zsimline@163.com)

#include "walkfire.h"
#include "common.h"
#include "cmdline.h"

using std::string;

void Download(const string start_url, const string cache_path_m3u8) {
  string filepath(cache_path_m3u8 + wfire::utils::MakeFilename(".m3u8"));
  wfire::downloader.DownloadM3U8(start_url, filepath);
  string next_url;
  while(wfire::m3u8parser.IsStreamInf(filepath)) {
    string backup_url =  wfire::m3u8parser.ExtractBackupUrl(filepath);
    wfire::utils::SpliceUrl(start_url, backup_url);
  }
}




int main(int argc, char *argv[]) {
  // 解析命令行参数
  std::map<string, string> parameters(wfire::ParseCmd(argc, argv));

  // 起始地址
  const string start_url(parameters["url"]);
  // 输出的文件名
  const string filename(parameters["filename"]);
  // 程序工作目录
  const string workspace(parameters["workspace"] + "/");


  // 检查工作目录
  const string cache_path(workspace + "cahce/");
  const string cache_path_m3u8(cache_path + "m3u8/");
  const string cache_path_ts(cache_path + "ts/");
  wfire::utils::CheckDir(workspace);
  wfire::utils::CheckDir(cache_path);
  wfire::utils::CheckDir(cache_path_m3u8);
  wfire::utils::CheckDir(cache_path_ts);


  return 0;
}
