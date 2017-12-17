#include <iostream>
#include <vector>

#include "Base.hpp"
#include "German.hpp"
#include "Italian.hpp"

using namespace std;

int main(int ac, char** av) {
  cout << "Hello World\n";

  vector<Base> langs;

  Base base("Charlie");
  German german("Charlie");
  Italian italian("Charlie");

  langs.push_back(german);
  langs.push_back(italian);
  langs.push_back(base);

  for (auto l : langs) {
    l.sayHi();
  }

  return 0;
}