// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 视频合并器

#ifndef WALKFIRE_CORE_COMBINE_H_
#define WALKFIRE_CORE_COMBINE_H_

#include <string>
#include <vector>

using std::string;

namespace wfspace {

class Combine {
private:
  // 输出视频文件的路径
  const string filepath_;

  // FFMPEG 合并视频命令
  const string tslist_file_path_;

  // 流媒体片段文件的存储路径列表
  const std::vector<string> ts_paths_;
  
  // 生成.tslist文件
  void MakeTsListFile() const;
  
public:
  Combine(string filepath, std::vector<string> ts_paths);
  ~Combine();

  void CombineVideo(string oformat) const;

};

}  // namespace wfspace

#endif  // WALKFIRE_CORE_COMBINE_H_