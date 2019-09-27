// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// M3U8文件内容解析器

#ifndef WALKFIRE_CORE_URLPARSER_H_
#define WALKFIRE_CORE_URLPARSER_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace wfire {

class M3U8Parser{
private:
  // 从M3U8文件中读取字符串
  // @param filepath M3U8文件存储路径
  // @return 读取到的字符串
  string ReadM3U8File(const string &filepath);

  // 判断一个文件是否为M3U8文件
  // @param rgx_string M3U8文件内容字符串
  // @return 文件是M3U8文件返回true,否则返回flase
  bool IsM3U8(const string &rgx_string);

  // 提取流媒体片段的链接
  // @param rgx_string M3U8文件内容字符串
  // @return 流媒体片段链接列表
  vector<string> ExtractTSUrls(const string &rgx_string);

  // 提取流媒体片段的时长
  // @param rgx_string M3U8文件内容字符串
  // @return 流媒体片段时长列表
  vector<string> ExtractExtInfs(const string &rgx_string);

  // 提取流媒体版本
  // @param rgx_string M3U8文件内容字符串
  int ExtractExtXVersion(const string &rgx_string);
  
  // 提取流媒体片段最大时长
  // @param rgx_string M3U8文件内容字符串
  int ExtractExtXTargetDuration(const string &rgx_string);
  
  // 提取第一个流媒体片段的序列号
  // @param rgx_string M3U8文件内容字符串
  int ExtractExtXMediaSequence(const string &rgx_string);

public:
  M3U8Parser();
  ~M3U8Parser();

  // 解析M3U8文件
  void ParserM3U8(const string &filepath);

  // 判断一个文件是否为M3U8备份源文件
  // @param filepath M3U8文件存储路径
  // @return 文件是M3U8备份源文件返回true,否则返回flase
  bool IsStreamInf(const string &filepath);

  // 从M3U8备份源文件中提取备份源地址
  // @param filepath M3U8文件存储路径
  // @return 提取到的M3U8备份原地址
  string ExtractBackupUrl(const string &filepath);

};

}  // namespace wfire

#endif  // WALKFIRE_CORE_URLPARSER_H_
