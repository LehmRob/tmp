#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <openssl/rsa.h>
#ifdef __cplusplus
}
#endif

namespace sign {
class RsaKey {
 public:
  RsaKey();
  ~RsaKey();
  void generate();
  RSA* getRsa();
  bool isGenerated();

 private:
  RSA* rsa;
  bool generated;
};
}  // namespace sign