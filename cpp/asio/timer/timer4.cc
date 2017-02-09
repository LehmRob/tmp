#include <iostream>

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class Printer 
{
public:
    Printer(boost::asio::io_service &io) 
    {
    }
    

private:
    boost::asio::deadline_timer timer1;
    boost::asio::deadline_timer timer2;
    int count;
}
    
