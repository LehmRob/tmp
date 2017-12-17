#include "Base.hpp"

#include <iostream>
#include <string>

using namespace std;

Base::Base(const char* msg) : _msg(msg) {}

void Base::sayHi() { cout << "Hi " << _msg << '\n'; }