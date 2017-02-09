#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <exception>

/**
 * Execute a system command and returns the stdout of the command
 * as string. If the command fails throw a exception.
 *
 * @param cmd Command which will be executed
 *
 * @return String with the standard out of the executed command
 */
std::string exec(const char* cmd)
{
    char buf[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        std::cout << "Throwing exception" << std::endl;
        throw std::runtime_error("popen() failed");
    }

    while (!feof(pipe.get())) {
        if (fgets(buf, 128, pipe.get()) != NULL) {
            result += buf;
        }
    }

    return result;
}

int main(int arg, char** argv)
{
    try {
        std::cout << "Result: " << exec("ls -l");
    } catch (std::exception &ex) {
        std::cerr << "Error occured" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
