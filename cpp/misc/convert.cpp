#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdio>
#include <cmath>

namespace {
  unsigned int kMaxSize = 5;

  long 
  convert(const std::vector<unsigned char>& data)
  {
    if (data.size() > kMaxSize) {
      throw std::range_error("Data is bigger than expected");
    }

    long value = 0;
    for (unsigned int i = 0; i < data.size(); i++) {
      value += (data[i] * (static_cast<int>(pow(0xff, i))));
    }

    return value;
  }
}

int
main(int ac, char** av)
{
  std::vector<unsigned char> v1{0x02};
std::vector<unsigned char> v2{0x00, 0x01};
  std::vector<unsigned char> v3{0x02, 0x02, 0x03};
  std::vector<unsigned char> v4{0x02, 0x03, 0x00, 0xc2};

  try {
      std::cout << "Result 1 " << ::convert(v1) << '\n';
      std::cout << "Result 1 " << ::convert(v2) << '\n';
      std::cout << "Result 1 " << ::convert(v3) << '\n';
      std::cout << "Result 1 " << ::convert(v4) << '\n';
  } catch (std::exception& ex) {
    std::cerr << ex.what();
  }
  return 0;
}
