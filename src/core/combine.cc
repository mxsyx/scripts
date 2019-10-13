// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 视频合并器

#include "combine.h"
#include <unistd.h>
#include <sstream>
#include <fstream>

using std::string;

namespace wfspace {

Combine::Combine(string filepath, std::vector<string> ts_paths):
                 filepath_(filepath), ts_paths_(ts_paths), 
                 tslist_file_path_(filepath_ + ".tslist"){}

Combine::~Combine() {}

void Combine::MakeTsListFile() const {
  std::ofstream stream(tslist_file_path_);
  if(stream) {
    string line;
    int ts_nums = ts_paths_.size();
    for(int i = 0; i < ts_nums; i++) {
      line = "file " + ts_paths_[i] + "\n";
      stream.write(line.c_str(), line.size());
    }
  }
}

void Combine::CombineVideo(string oformat) const {
  MakeTsListFile();

  // 生成FFMPEG合并视频的命令
  std::ostringstream command;
  command << "ffmpeg -f concat -safe 0 -i "
          << tslist_file_path_ << " -c copy "
          << filepath_ << "." << oformat;
  string cmd(command.str());

  FILE *fp;
  if ((fp = popen(cmd.c_str(), "r")) != NULL) {
    pclose(fp);
  }
}

}  // namespace wfspace
