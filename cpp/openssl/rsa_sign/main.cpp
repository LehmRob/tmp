#include <iostream>
#include "key_pair.hpp"
#include "sign.hpp"
#include "verify.hpp"

using std::cout;

int main(int ac, char** av) {
  std::cout << "Hello World\n";

  sign::KeyPair keyPair;
  keyPair.generate();
  const char data[] = "hello_friend\n";

  auto signature = sign::signIt(keyPair, data, sizeof(data));

  signature.printIt();

  if (sign::isSignatureValid(signature, keyPair, data, sizeof(data))) {
    std::cout << "Signature is valid\n";
  } else {
    std::cout << "Signature is NOT valid\n";
  }

  return 0;
}