#ifndef __HELLO_WORLD_SERVER_HPP__
#define __HELLO_WORLD_SERVER_HPP__

#include <string>

namespace hello_server {
	class Server {
	public:
		Server(std::string name) : my_name(name) {}
		std::string GetName(void);
	private:
		std::string my_name;
	};
} // namespace hello_server

#endif // __HELLO_WORLD_SERVER_HPP__
