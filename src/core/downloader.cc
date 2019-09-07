//

#include <curl/curl.h>
#include "../include/walkfire/downloader.h"

using std::string;
using wfire::Downloader;

size_t Downloader::WriteData(void *ptr, size_t size, 
                             size_t nmemb, void *fp) {
  int written = fwrite(ptr, size, nmemb, (FILE *)fp);
  return written;
}

void Downloader::download(string url) {
  FILE *fp = fopen("aa", "wb");
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
  //res = curl_easy_perform(curl);
}



