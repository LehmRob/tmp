#include <iostream>
#include <thread>
#include <future>
#include <string>

using namespace std;

int main(int argc, char** argv) 
{
    future<string> f = async(launch::async,
                             [](const string& n) { return n + "world"; },
                             "hello");
    f.wait();
    
    try {
        cout << f.get() << endl;
    } catch (exception& e) {
        cerr << e.what() << endl;
    }
    
    return 0;
}
