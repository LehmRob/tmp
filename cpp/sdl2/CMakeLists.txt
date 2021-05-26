cmake_minimum_required(VERSION 3.10)
project(demo-sdl2)

find_package(SDL2 REQUIRED)

add_executable(demo-sdl2 
    main.cxx
    app.cxx
    )
target_include_directories(demo-sdl2 PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(demo-sdl2 ${SDL2_LIBRARIES})
