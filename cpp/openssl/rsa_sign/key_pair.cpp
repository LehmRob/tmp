#include "key_pair.hpp"

#include <stdexcept>

extern "C" {
#include <openssl/err.h>
#include <openssl/evp.h>
}

namespace sign {
KeyPair::KeyPair() {}

KeyPair::~KeyPair() { freeKeys(); }

void KeyPair::generate() {
  rsa->generate();
  allocateKeys();
  assignPrivateKey();
  assignPublicKey();
}

EVP_PKEY* KeyPair::getPublicKey() { return publicKey; }

EVP_PKEY* KeyPair::getPrivateKey() { return privateKey; }

void KeyPair::allocateKeys() {
  publicKey = EVP_PKEY_new();
  if (publicKey == nullptr) {
    throw std::runtime_error("Can't allocate memory for public key");
  }

  privateKey = EVP_PKEY_new();
  if (privateKey == nullptr) {
    throw std::runtime_error("Can't allocate memory for private key");
  }
}

void KeyPair::assignPrivateKey() {
  auto ret = EVP_PKEY_assign_RSA(privateKey, RSAPrivateKey_dup(rsa->getRsa()));
  if (ret != 1) {
    throw std::runtime_error("Can't assign private key");
  }
}

void KeyPair::assignPublicKey() {
  auto ret = EVP_PKEY_assign_RSA(publicKey, RSAPublicKey_dup(rsa->getRsa()));
  if (ret != 1) {
    throw std::runtime_error("Can't assign public key");
  }
}

void KeyPair::freeKeys() {
  if (privateKey != nullptr) {
    EVP_PKEY_free(privateKey);
  }
  if (publicKey != nullptr) {
    EVP_PKEY_free(publicKey);
  }
}
}  // namespace sign