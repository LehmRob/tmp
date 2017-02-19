find_package(LibSSH)

add_executable(ssh_example ssh_example.cpp)
target_link_libraries(ssh_example ${LIBSSH_LIBRARIES})
