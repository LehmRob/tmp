add_library(server STATIC server.cpp)
add_executable(hello_server main.cpp)
target_link_libraries(hello_server server)
