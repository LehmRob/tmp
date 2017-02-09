#include "server.hpp"

#include <string>

namespace hello_server {
	using namespace std;

	string Server::GetName() {
		return this->my_name;
	}
} // namespace hello_server
