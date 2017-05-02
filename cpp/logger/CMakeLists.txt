cmake_minimum_required(VERSION 3.1.0)
project(cpp_asio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(spdlog)
add_subdirectory(blackhole)
#add_subdirectory(glog)
