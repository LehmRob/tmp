cmake_minimum_required(VERSION 3.3)
project(served_example)

set(SERVED_BUILD_SHARED OFF CACHE BOOL "Don't build shared lib" FORCE)
set(SERVED_BUILD_STATIC ON CACHE BOOL "Building static lib" FORCE)
set(SERVED_BUILD_EXAMPLES OFF CACHE BOOL "Don't build examples" FORCE)
set(SERVED_BUILD_TESTS OFF CACHE BOOL "Don't build tests" FORCE)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/served/src)

add_subdirectory(3rdparty/served)

add_executable(http http.cc)
target_link_libraries(http served)
