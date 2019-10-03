#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>
#include <vector>

using std::cout;
using std::string;

namespace dd {

int main() {
  std::ifstream fin("/home/mxsyx/desktop/m.m3u8");
  if(fin) {
    fin.seekg(0, fin.end);
    const int buffer_length = fin.tellg();
    fin.seekg(0, fin.beg);
    char buffer[buffer_length];
    fin.read(buffer, buffer_length);
    fin.close();
    const string rgx_string(buffer, buffer_length);
    boost::regex rgx("(?<=\n)[^#].*");
    boost::smatch search_result;
    boost::regex_search(rgx_string,search_result, rgx);
    cout << search_result[0];
  }
  return 0;
}
}