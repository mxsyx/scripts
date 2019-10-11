// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 视频合并器

#ifndef WALKFIRE_CORE_COMBINE_H_
#define WALKFIRE_CORE_COMBINE_H_

#include <string>
#include <vector>
#include "videometa.h"

using std::string;

namespace wfspace {

class Combine {
private:
  // 输出的视频文件路径
  string filepath_;
  // 流媒体片段文件的存储路径列表
  std::vector<string> ts_paths_;

public:
  Combine(string filepath, std::vector<string> ts_paths);
  ~Combine();

  void MakeCombineFile(const string &combine_filepath) const;

  void CombineVideo() const;

};

}  // namespace wfspace

#endif  // WALKFIRE_CORE_COMBINE_H_