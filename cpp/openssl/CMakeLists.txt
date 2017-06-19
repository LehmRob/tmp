project(openssl_example)
cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenSSL REQUIRED)

add_executable(md5 md5.cpp)
target_link_libraries(md5 ${OPENSSL_LIBRARIES})