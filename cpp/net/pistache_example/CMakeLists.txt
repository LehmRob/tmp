project(pistache_example)
cmake_minimum_required(VERSION 3.3)

add_subdirectory(3rdparty/pistache)

add_executable(restserv rest_server.cpp)
target_link_libraries(restserv pistache)