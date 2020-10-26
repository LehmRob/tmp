cmake_minimum_required(VERSION 3.10)
project(demo-sdl2)

set(SDL_SHARED OFF CACHE BOOL "Disable SDL Shared")
set(SDL_STATIC ON CACHE BOOL "Enable SDL Static")

include(FetchContent)
FetchContent_Declare(libsdl2
	URL https://libsdl.org/release/SDL2-2.0.12.tar.gz
	)

FetchContent_GetProperties(libsdl2)
if (NOT libsdl2_POPULATED)
	FetchContent_Populate(libsdl2)
	add_subdirectory(${libsdl2_SOURCE_DIR} ${libsdl2_BINARY_DIR})
endif()