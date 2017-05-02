cmake_minimum_required(VERSION 3.1.0)
project(pty)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(pty_master pty_master.cc)
add_executable(pty_slave pty_slave.cc)
