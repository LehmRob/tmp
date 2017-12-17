#include <iostream>
#include <memory>
#include <mutex>
#include <stack>
#include <thread>

using std::cout;
using std::thread;
using std::mutex;
using std::shared_ptr;
using std::stack;

class Pipe {
 public:
 private:
  mutex lock;
  stack<int> stack;
};

class Producer {
 public:
  Producer(shared_ptr<Pipe> pipe, const int startCount = 0,
           const int maxCount = 255)
      : pipe(pipe),
        startCount(startCount),
        maxCount(maxCount),
        counter(startCount) {}

  void fireAndForget() {
    for (int i = startCount; i <= maxCount; i++) {
    }
  }

 private:
  int counter;
  const int startCount;
  const int maxCount;
  shared_ptr<Pipe> pipe;
};

class Consumer {};

int main(int ac, char** av) {
  cout << "Hello Friend\n";
  return 0;
}
