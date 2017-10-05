#pragma once

#include "key_pair.hpp"
#include "signature.hpp"

namespace sign {
Signature signIt(KeyPair& pair, const char* data, int len);
}