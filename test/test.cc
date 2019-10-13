#include <iostream>
#include <sstream>

using std::string;

class Dev {
private:
  int dev_ = 5;

public:
  const string a_;
  const string b_;
  Dev(string a);
  ~Dev();

  const int& dev();
};

Dev::Dev(string a):a_(a), b_(a + "xxx") {}
Dev::~Dev() {}
const int& Dev::dev() { return dev_; }

int main() {
  Dev dev("ll");
  std::cout << dev.b_;
}
