#pragma once

#include <string>

class Base {
 public:
  Base(const char* msg);
  virtual void sayHi();

 protected:
  std::string _msg;
};