// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 作者：江南的茶叶有甜 (zsimline@163.com)

#include "common.h"
#include "cmdline.h"
#include "videometa.h"
#include "m3u8parser.h"
#include "downloader.h"

using std::string;

int main(int argc, char *argv[]) {
  // 解析命令行参数
  std::map<string, string> parameters = wfire::ParseCmd(argc, argv);
  
  // 视频源信息对象
  wfire::VideoMeta videometa;
  // M3U8文件的链接
  const string url(parameters["url"]);
  // 程序工作目录
  const string workspace(parameters["dir"] + "/");

  // 检查工作目录
  wfire::utils::CheckDir(workspace);

  videometa.append_streaminf(url);
  
  const string filepath = workspace + wfire::utils::MakeFilename(".m3u8");

  wfire::Downloader downloader;
  downloader.DownloadM3U8(url, filepath);

  wfire::M3U8Parser m3u8parser;
  std::cout << m3u8parser.IsStreamInf(filepath);
  return 0;
}
