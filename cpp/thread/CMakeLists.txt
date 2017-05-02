cmake_minimum_required(VERSION 3.1.0)
project(cpp_asio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(thread1 thread1.cpp)
target_link_libraries(thread1 Threads::Threads)
add_executable(thread2 thread2.cpp)
target_link_libraries(thread2 Threads::Threads)
