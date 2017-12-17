#include "Italian.hpp"

#include <iostream>

using namespace std;

Italian::Italian(const char* msg) : Base(msg) {}

void Italian::sayHi() { cout << "Bon Jorno " << Base::_msg << '\n'; }
