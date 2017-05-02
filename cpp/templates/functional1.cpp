#include <functional>
#include <iostream>

void print_animal(const char* msg) {
  std::cout << "Animal: " << msg << std::endl;
}

void call_back_handler(std::function<void(const char*)> f, const char* msg) {
  for (int i = 0; i < 3; i++) {
	std::cout << "Round " << i;
	f(msg);
  }
}

int main(int argc, char** argv) {
  std::cout << "I'm Groot!!" << std::endl;

  std::function<void(const char*)> f1 = print_animal;

  f1("Elephant");
  call_back_handler(print_animal, "Wartog");
  return 0;
}
