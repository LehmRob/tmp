#include <iostream>
#include <chrono>
#include <thread>

void foo(void) 
{
    for (auto i = 0; i < 100; i++) {
        std::cout << "hello world from foo bar" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main(int argc, char** argv) 
{
    std::thread first(foo); // this spawn the thread and calls foo

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Starting Joining" << std::endl;
    
    first.join();

    std::cout << "COmpleted" << std::endl;
    
    return 0;
}

