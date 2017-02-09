// Use classes instead of callback functions

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class Printer {
public:
	Printer(boost::asio::io_service& io)
		: timer(io, boost::posix_time::seconds(1)),
		  count(0) 
    {
        timer.async_wait(boost::bind(&Printer::print, this));
    }
	~Printer()
    {
        std::cout << "It's your final countdown " << count << std::endl;
    }

	void print()
    {
        if (count < 5) {
            std::cout << count << std::endl;
            ++count;
				
            timer.expires_at(timer.expires_at() + 
                             boost::posix_time::seconds(1));
            timer.async_wait(boost::bind(&Printer::print, this));
        }
    }

private:
	boost::asio::deadline_timer timer;
	int count;

};

int main(int argc, char** argv)
{
	std::cout << "Hello World" << std::endl;
    boost::asio::io_service io;
    Printer p(io);
    
    io.run();
    
	return 0;
}
