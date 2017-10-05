project(openssl_example)
cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenSSL REQUIRED)

add_executable(md5 md5.cpp)
target_link_libraries(md5 ${OPENSSL_LIBRARIES})

list(APPEND rsa_sign_SRCS 
  rsa_sign/main.cpp
  rsa_sign/rsa_key.cpp
  rsa_sign/key_pair.cpp
  rsa_sign/sign.cpp
  rsa_sign/signature.cpp
  rsa_sign/verify.cpp
  )

add_executable(rsa_sign ${rsa_sign_SRCS})
target_link_libraries(rsa_sign ${OPENSSL_LIBRARIES})