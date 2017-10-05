#pragma once

#include "key_pair.hpp"
#include "signature.hpp"

namespace sign {
bool isSignatureValid(Signature& signature, KeyPair& keyPair, const char* msg,
                      size_t len);
}  // namespace sign