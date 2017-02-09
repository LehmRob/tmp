cmake_minimum_required(VERSION 3.1.0)
project(examples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(pty)
add_subdirectory(logger)
add_subdirectory(asio)
#add_subdirectory(gtest)
add_subdirectory(thread)
add_subdirectory(cmd)
add_subdirectory(ssh)
