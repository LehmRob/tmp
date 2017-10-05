#include "rsa_key.hpp"

#include <iostream>
#include <stdexcept>

extern "C" {
#include <openssl/bn.h>
#include <openssl/rsa.h>
}

namespace sign {

namespace {
auto KEY_SIZE = 2048;
}

RsaKey::RsaKey() {
  this->rsa = RSA_new();
  if (this->rsa == nullptr) {
    throw std::runtime_error("Unable to malloc RSA key structure");
  }
}

RsaKey::~RsaKey() {
  if (this->rsa != nullptr) {
    RSA_free(this->rsa);
  }
}

void RsaKey::generate() {
  auto bn = BN_new();
  BN_set_word(bn, RSA_F4);
  auto ret = RSA_generate_key_ex(this->rsa, KEY_SIZE, bn, nullptr);
  if (ret != 1) {
    throw std::runtime_error("Error during key generation");
  }

  this->generated = true;
}

RSA* RsaKey::getRsa() { return this->rsa; }

bool RsaKey::isGenerated() { return this->generated; }
}  // namespace sign