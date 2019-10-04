// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 全局状态文件

#ifndef WALKFIRE_CORE_GLOBAL_H_
#define WALKFIRE_CORE_GLOBAL_H_

#include <string>

using std::string;

namespace wfire {

class Global {
private:
  // 起始地址
  string starturl_;

  // 输出的文件名
  string filename_;

  // 程序工作目录
  string workspace_;

  // 缓存文件根目录
  string cache_path_;

  // M3U8文件缓存目录
  string cache_path_m3u8_;

  // TS文件缓存目录
  string cache_path_ts_;

  // M3U8文件的存储路径
  string m3u8_filepath_;

  // 判断目录是否存在
  // 若不存在则新建目录
  void CheckDir(const string &dir);

public:
  Global(int argc, char *argv[]);
  ~Global();

  // 执行程序初始化
  // 检查工作目录是否存在
  void Initialization();

  // 设置起始地址
  void set_starturl(string starturl);

  // 设置M3U8文件存储路径
  void set_m3u8_filepath(string m3u8_filepath);

  // 返回起始地址
  string starturl() const;

  // 返回M3U8文件缓存目录
  string cache_path_m3u8() const;

  // 返回TS文件缓存目录
  string cache_path_ts() const;

  string m3u8_filepath() const;

};

}  // namespace wfire 

#endif  // WALKFIRE_CORE_GLOBAL_H_
