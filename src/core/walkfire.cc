// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制

#include "utils.h"
#include "cmdline.h"
#include "videometa.h"
#include "downloader.h"

using std::string;

// 视频源信息对象
wfire::VideoMeta videometa;


int main(int argc, char *argv[]) {
  std::map<string, string> parameters = wfire::ParseCmd(argc, argv);
  
  string url(parameters["url"]);
  string workspace(parameters["dir"]);

  // 检查工作目录
  wfire::utils::CheckDir(workspace);


  wfire::StreamInf streaminf(url);
  videometa.append_streaminf(streaminf);
  
  wfire::Downloader downloader;

  downloader.DownloadM3U8(url, workspace);

  return 0;
}
