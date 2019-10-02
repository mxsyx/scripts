// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 作者：江南的茶叶有甜 (zsimline@163.com)

#include "walkfire.h"
#include "common.h"
#include "cmdline.h"

using std::string;

// 下载M3U8索引文件
// 如果下载的文件不是最终包含TS文件链接的M3U8文件，
// 而是指向了一个M3U8备份文件，则去下载这个备份文件
// @param next_url 下一个将被下载的文件的链接
// @param cache_path_m3u8 M3U8文件的缓存目录
string DownloadM3U8(string next_url, const string &cache_path_m3u8) {
  string filepath;  // 下载的M3U8文件存储路径
  string backup_url;  // M3U8备份文件的链接
  do {
    filepath = cache_path_m3u8 + wfire::utils::MakeFilename(".m3u8");
    wfire::downloader.DownloadM3U8(next_url, filepath);
    wfire::m3u8parser.ChangeRgxString(filepath);
    if(wfire::m3u8parser.IsStreamInf()) {
      backup_url = wfire::m3u8parser.ExtractBackupUrl();
      next_url = wfire::utils::SpliceUrl(next_url, backup_url);
      std::cout << next_url << std::endl;
    } else {
      next_url = "";
    }
  } while(!next_url.empty());
  return filepath;
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

  const string m3u8_filepath(DownloadM3U8(start_url, cache_path_m3u8));
  
  return 0;
}
