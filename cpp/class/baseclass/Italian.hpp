#pragma once

#include <string>

#include "Base.hpp"

class Italian : public Base {
 public:
  Italian(const char* msg);
  void sayHi() override;
};