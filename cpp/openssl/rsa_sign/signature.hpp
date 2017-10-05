#pragma once

#include <vector>

namespace sign {
class Signature {
 public:
  Signature(const unsigned char* signature, int len);
  void printIt();
  std::vector<unsigned char> getSignature();

 private:
  std::vector<unsigned char> signature;
};
}