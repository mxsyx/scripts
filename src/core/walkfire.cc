// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 作者：梦醒时夜续 (zsimline@163.com)





int main(int argc, char *argv[]) {
  


  const string m3u8_filepath(wfire::DownloadM3U8(start_url, cache_path_m3u8));
  wfire::SetVideoMeta(m3u8_filepath);
  wfire::DownloadTS(cache_path_ts);
  return 0;
}
