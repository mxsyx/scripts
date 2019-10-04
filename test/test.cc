#include <iostream>
#include <thread>
#include <curl/curl.h>

using std::string;

int WriteData(void *ptr, size_t size, size_t nmemb, void *fp) {
  int written = fwrite(ptr, size, nmemb, (FILE *)fp);
  return written;
}

void DownloadTS(string url, string filepath) {
  CURL *curl = curl_easy_init();
  FILE *fp = fopen(filepath.c_str(), "w");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
  curl_easy_perform(curl);
  fclose(fp);
  std::cout << "片段已保存到：" << filepath << std::endl;

  curl_easy_cleanup(curl);
}




int main() {
  curl_global_init(CURL_GLOBAL_ALL);
  std::thread t0(DownloadTS, "https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/d3e16be0f43000000.ts","a.ts");
  std::thread t1(DownloadTS, "https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/d3e16be0f43000001.ts","b.ts");
  std::thread t2(DownloadTS, "https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/d3e16be0f43000002.ts","c.ts");
  std::thread t3(DownloadTS, "https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/d3e16be0f43000003.ts","d.ts");
  std::thread t4(DownloadTS, "https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/d3e16be0f43000004.ts","e.ts");
  std::thread t5(DownloadTS, "https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/d3e16be0f43000005.ts","f.ts");
  std::thread t6(DownloadTS, "https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/d3e16be0f43000006.ts","g.ts");
  std::thread t7(DownloadTS, "https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/d3e16be0f43000007.ts","h.ts");
  std::thread t8(DownloadTS, "https://youku.com-ok-163.com/20190905/1200_a8048943/1000k/hls/d3e16be0f43000008.ts","i.ts");
  t0.join();
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  curl_global_cleanup();
  return 0;
}
