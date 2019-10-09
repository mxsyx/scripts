#include <iostream>
#include <thread>

using std::string;


int a = 8;
class Test {
private:
public:
  void Thread(int &n) {
    std::cout << "线程" << n << "开始" << std::endl;
  }
  void ThreadStart() {
    std::thread t0(&Test::Thread, this, std::ref(a));
    t0.join();
  }
};


int main() {
  Test test;
  test.ThreadStart();
  return 0;
}
