#include "signature.hpp"

#include <cstdio>
#include <vector>

namespace sign {
Signature::Signature(const unsigned char* signature, int len) {
  for (int i = 0; i < len; i++) {
    this->signature.push_back(signature[i]);
  }
}

std::vector<unsigned char> Signature::getSignature() { return this->signature; }

void Signature::printIt() {
  for (auto e : signature) {
    std::printf("%02x", e);
  }
  printf("\n");
}
}