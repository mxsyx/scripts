// 版权所有 (c) 2019 - WalkFire 作者保留所有权利
// 该软件源代码受 GNU GENERAL PUBLIC LICENSE 控制
// 作者：梦醒时夜续 (zsimline@163.com)

#include "master.h"

int main(int argc, char *argv[]) {
  wfire::Global global(argc, argv);
  global.Initialization();
  wfire::Master master(global);
  master.Start();
}
