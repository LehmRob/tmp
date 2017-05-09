#include <iostream>
#include <string>
#include <ctime>

#include <served/served.hpp>

std::string GetTime() {
  return std::string(std::asctime(std::time_t(nullptr)));
}

int main(int argc, char** argv) {
  served::multiplexer mux;

  mux.handle("/hello").get([](served::response &res, const served::request &req) {
	res << "Hello World ";
  });

  mux.handle("/").get([](served::response &res, const served::request &req) {
	res << "Try /hello";
  });

  served::net::server s("127.0.0.1", "8080", mux);
  s.run(10);
  
  return 0;
}
