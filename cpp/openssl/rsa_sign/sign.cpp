#include "sign.hpp"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <tuple>

extern "C" {
#include <openssl/evp.h>
}

#include "key_pair.hpp"
#include "signature.hpp"

namespace sign {

namespace {
std::tuple<EVP_MD_CTX*, const EVP_MD*> initSigning(KeyPair& pair,
                                                   const char* data, int len) {
  OpenSSL_add_all_algorithms();

  auto ctx = EVP_MD_CTX_create();
  if (ctx == nullptr) {
    throw std::runtime_error("Creation of context failed");
  }

  auto md = EVP_get_digestbyname("SHA256");
  if (md == nullptr) {
    throw std::runtime_error("Can't get digest SHA512");
  }

  auto ret = EVP_DigestInit_ex(ctx, md, nullptr);
  if (ret != 1) {
    throw std::runtime_error("Can't initialize digist");
  }

  std::cout << "Reach here\n";

  ret = EVP_DigestSignInit(ctx, nullptr, md, nullptr, pair.getPrivateKey());
  if (ret != 1) {
    throw std::runtime_error("Can't initialize signing digest");
  }

  ret = EVP_DigestSignUpdate(ctx, data, len);
  if (ret != 1) {
    throw std::runtime_error("Can't sign data");
  }

  return std::make_tuple(ctx, md);
}

size_t getSignatureSize(std::tuple<EVP_MD_CTX*, const EVP_MD*>& signData) {
  auto ctx = std::get<0>(signData);
  size_t len = 0;

  auto ret = EVP_DigestSignFinal(ctx, nullptr, &len);
  if (ret != 1) {
    throw std::runtime_error("Can't determine length of signature");
  }

  return len;
}

Signature createSignature(std::tuple<EVP_MD_CTX*, const EVP_MD*> signData) {
  auto len = getSignatureSize(signData);
  unsigned char* signature = (unsigned char*)OPENSSL_malloc(len);
  if (signature == nullptr) {
    throw std::runtime_error("Can't allocate memory for signature");
  }

  auto ctx = std::get<0>(signData);
  auto ret = EVP_DigestSignFinal(ctx, signature, &(len));
  if (ret != 1) {
    throw std::runtime_error("Signature creation has failed");
  }

  Signature s(signature, len);
  OPENSSL_free(signature);

  return s;
}
}  // namespace

Signature signIt(KeyPair& pair, const char* data, int len) {
  auto sign = initSigning(pair, data, len);
  return createSignature(sign);
}

}  // namespace sign