cmake_minimum_required(VERSION 3.3)
project(libarchive-examples VERSION 1.0.0 LANGUAGES C)

find_package(LibArchive REQUIRED)

add_executable(untar untar.c)
target_include_directories(untar PRIVATE ${LibArchive_INCLUDE_DIRS})
target_link_libraries(untar ${LibArchive_LIBRARIES})
