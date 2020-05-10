cmake_minimum_required(VERSION 3.3)
project(served_example)

set(CMAKE_CXX_STANDARD 11)

set(SERVED_BUILD_SHARED OFF CACHE BOOL "Don't build shared lib" FORCE)
set(SERVED_BUILD_STATIC ON CACHE BOOL "Building static lib" FORCE)
set(SERVED_BUILD_EXAMPLES OFF CACHE BOOL "Don't build examples" FORCE)
set(SERVED_BUILD_TESTS OFF CACHE BOOL "Don't build tests" FORCE)

find_package(Threads)

include(ExternalProject)
ExternalProject_Add(served-lib
	URL https://github.com/meltwater/served/archive/v1.6.0.tar.gz
	INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/served
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
	           -DSERVED_BUILD_STATIC:BOOL=ON
	           -DSERVED_BUILD_SHARED:BOOL=OFF
	           -DSERVED_BUILD_EXAMPLES:BOOL=OFF
	           -DSERVED_BUILD_TESTS:BOOL=OFF
)

add_executable(http http.cc)
target_include_directories(http PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/served/include)
target_link_libraries(http Threads::Threads ${CMAKE_CURRENT_BINARY_DIR}/served/lib/libserved.a)

include(FetchContent)
FetchContent_Declare(served-lib-fetch
	URL https://github.com/meltwater/served/archive/v1.6.0.tar.gz
)

FetchContent_GetProperties(served-lib-fetch)

if(NOT served-lib-fetch_POPULATED)
	FetchContent_Populate(served-lib-fetch)
	add_subdirectory(${served-lib-fetch_SOURCE_DIR} ${served-lib-fetch_BINARY_DIR})
endif()

add_executable(http-fetch http.cc)
target_include_directories(http-fetch PUBLIC 
	${served-lib-fetch_SOURCE_DIR}/src)
target_link_libraries(http-fetch 
	Threads::Threads 
	${served-lib-fetch_SOURCE_DIR}/lib/libserved.a
	)

