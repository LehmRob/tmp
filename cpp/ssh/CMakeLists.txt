find_package(LibSSH REQUIRED)

add_executable(simple_example simple_example.cpp)
target_link_libraries(simple_example ${LIBSSH_LIBRARIES})
