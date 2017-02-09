#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& e)
{
	std::cout << "Hello World from print" << std::endl;
}

int main(int argc, char **argv)
{
	boost::asio::io_service io;

	std::cout << "Sync Timer" << std::endl;
	boost::asio::deadline_timer tsync(io, boost::posix_time::seconds(5));
	std::cout << "Hello world before" << std::endl;
	tsync.wait();
	std::cout << "Hello World after" << std::endl;

	std::cout << "Async timer" << std::endl;
	boost::asio::deadline_timer tasync(io, boost::posix_time::seconds(5));
	tasync.async_wait(&print);

	io.run();
	return 0;
}
