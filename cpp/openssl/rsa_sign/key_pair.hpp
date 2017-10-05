#pragma once

#include <memory>

extern "C" {
#include <openssl/evp.h>
}

#include "rsa_key.hpp"

namespace sign {
class KeyPair {
 public:
  KeyPair();
  ~KeyPair();
  void generate();
  EVP_PKEY* getPublicKey();
  EVP_PKEY* getPrivateKey();

 private:
  void allocateKeys();
  void freeKeys();
  void assignPrivateKey();
  void assignPublicKey();

  std::unique_ptr<RsaKey> rsa = std::unique_ptr<RsaKey>(new RsaKey);
  EVP_PKEY* publicKey;
  EVP_PKEY* privateKey;
};
}