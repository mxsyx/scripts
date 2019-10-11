// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 视频合并器



#include "combine.h"
#include <unistd.h>
#include <fstream>
#include <iostream>

using std::string;

namespace wfspace {

Combine::Combine(string filepath, std::vector<string> ts_paths) {
  filepath_ = filepath;
  ts_paths_ = ts_paths;
}

Combine::~Combine() {}

void Combine::MakeCombineFile(const string &combine_filepath) const {
  std::ofstream stream(combine_filepath);
  if(stream) {
    int ts_nums = ts_paths_.size();
    for(int i = 0; i < ts_nums; i++) {
      string command("file " + ts_paths_[i] + "\n");
      stream.write(command.c_str(), command.size());
    }
  }
}

void Combine::CombineVideo() const {
  string combine_filepath = filepath_ + ".cmb";
  MakeCombineFile(combine_filepath);
  std::cout << combine_filepath;
  string cmd = "ffmpeg -f concat -safe 0 -i " + combine_filepath
               + " -c copy " + filepath_ + ".mp4";
  FILE *fp;
  if ((fp = popen(cmd.c_str(), "r")) != NULL) {
    pclose(fp);
  }
  std::cout << cmd;
}

}  // namespace wfspace

