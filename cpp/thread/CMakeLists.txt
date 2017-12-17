cmake_minimum_required(VERSION 3.3)
project(cpp_thread)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

add_executable(thread1 thread1.cpp)
target_link_libraries(thread1 Threads::Threads)

add_executable(thread2 thread2.cpp)
target_link_libraries(thread2 Threads::Threads)

add_executable(mutex_data mutex_data.cpp)
target_link_libraries(mutex_data Threads::Threads)
