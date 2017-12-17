#include <iostream>

#include <endpoint.h>

using std::cout;
using namespace Pistache::Http;
using namespace Pistache::Net;

struct MyHandler : public Handler {
  HTTP_PROTOTYPE(MyHandler)

  void onRequest(const Request& request, ResponseWriter writer) {
    response.send(Code::Ok, "Hello World");
  }
}

int main(int ac, char* av[]) {
  cout << "Hello World\n";
  Net::Address addr(Net::Ipv4::any(), Net::Port(9080));
  auto opts = Net::Http::Endpoint::options.threads(1);
}