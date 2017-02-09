#include <iostream>
#include <spdlog/spdlog.h>

int main(int argc, char **argv) {
	namespace spd = spdlog;

	std::cout << "Hello World" << std::endl;

    auto cons = spd::stdout_logger_mt("cons", true);

    cons->set_level(spd::level::debug); // Set specific logger's log level
    cons->info("Welcome to spdlog!");
    cons->debug("This is a debug output");
	return 0;
}