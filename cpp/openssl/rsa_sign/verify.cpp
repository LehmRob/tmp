#include "verify.hpp"

#include <cstdio>
#include <iostream>
#include <stdexcept>

extern "C" {
#include <openssl/evp.h>
}

#include "key_pair.hpp"
#include "signature.hpp"

using std::runtime_error;
using std::cout;

namespace sign {

namespace {

void freeContext(EVP_MD_CTX* ctx) {
  EVP_MD_CTX_destroy(ctx);
  ctx = nullptr;
}

EVP_MD_CTX* begin(KeyPair& keyPair) {
  OpenSSL_add_all_algorithms();
  auto ctx = EVP_MD_CTX_create();
  if (ctx == NULL) {
    throw runtime_error("Can't create context");
  }

  auto md = EVP_get_digestbyname("SHA256");
  if (md == NULL) {
    freeContext(ctx);
    throw runtime_error("Can't get digest by name");
  }

  auto ret = EVP_DigestInit_ex(ctx, md, nullptr);
  if (ret != 1) {
    freeContext(ctx);
    throw runtime_error("Can't init digest");
  }

  ret = EVP_DigestVerifyInit(ctx, nullptr, md, nullptr, keyPair.getPublicKey());
  if (ret != 1) {
    freeContext(ctx);
    throw runtime_error("Can't init verfifing");
  }
  return ctx;
}

void addMessage(EVP_MD_CTX* ctx, const char* msg, size_t len) {
  auto ret = EVP_DigestVerifyUpdate(ctx, msg, len);
  if (ret != 1) {
    throw runtime_error("Can't add message to verifing");
  }
}

bool isVerified(EVP_MD_CTX* ctx, Signature& sig) {
  auto ret = EVP_DigestVerifyFinal(ctx, sig.getSignature().data(),
                                   sig.getSignature().size());
  if (ret != 1) {
    return false;
  }

  return true;
}

}  // namespace

bool isSignatureValid(Signature& signature, KeyPair& keyPair, const char* msg,
                      size_t len) {
  EVP_MD_CTX* ctx = begin(keyPair);
  addMessage(ctx, msg, len);

  auto result = isVerified(ctx, signature);
  freeContext(ctx);
  return result;
}

}  // namespace sign