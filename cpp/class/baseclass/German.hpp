#pragma once

#include <string>

#include "Base.hpp"

class German : public Base {
 public:
  German(const char* msg);
  void sayHi() override;
};