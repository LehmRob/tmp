#include <iostream>
#include <ctime>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string MakeDayTimeString()
{
    std::time_t now = std::time(0);
    return ctime(&now);
}

int main(int argc, char** argv)
{
    try {
        boost::asio::io_service io;
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8123));
        
        for(;;) {
            tcp::socket socket(io);
            std::cout << "Waiting for connection" << std::endl;
            acceptor.accept(socket);
            
            auto day_time = MakeDayTimeString();
            boost::system::error_code error;
            boost::asio::write(socket, boost::asio::buffer(day_time), 
                               error);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

            
