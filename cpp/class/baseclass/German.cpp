#include "German.hpp"

#include <iostream>

using namespace std;

German::German(const char* msg) : Base(msg) {}

void German::sayHi() { cout << "Guten Tag " << Base::_msg << '\n'; }