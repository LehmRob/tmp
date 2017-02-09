find_package (Threads)
add_definitions("-std=c++11")
add_executable(client client.cc)
add_executable(server server.cc)
target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

