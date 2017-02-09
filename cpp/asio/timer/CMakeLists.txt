add_executable(timer1 timer.cc)
add_executable(timer2 timer2.cc)
add_executable(timer3 timer3.cc)

target_link_libraries(timer1 ${Boost_LIBRARIES})
target_link_libraries(timer2 ${Boost_LIBRARIES})
target_link_libraries(timer3 ${Boost_LIBRARIES})

