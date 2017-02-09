find_package(Boost 1.58 REQUIRED COMPONENTS system date_time)
include_directories(${Boost_INCLUDE_DIRECTORIES})
link_directories(${Boost_LIBRARY_DIRS})

# add_subdirectory(hello_server)
add_subdirectory(timer)
add_subdirectory(socket)
