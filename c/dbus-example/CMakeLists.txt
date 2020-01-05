cmake_minimum_required(VERSION 3.6)

project(dbus-example VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS-GLIB REQUIRED dbus-glib-1)

include(CMakePrintHelpers)
cmake_print_variables(DBUS-GLIB_FOUND DBUS-GLIB_LDFLAGS DBUS-GLIB_INCLUDE_DIRS)

add_definitions(-DDBUS_SAMPLE_VERSION=\"${CMAKE_PROJECT_VERSION}\")

add_executable(dbus-server dbus-server.c)
target_include_directories(dbus-server PRIVATE ${DBUS-GLIB_INCLUDE_DIRS})
#include_directories(${DBUS-GLIB_INCLUDE_DIRS})
target_link_libraries(dbus-server PRIVATE ${DBUS-GLIB_LDFLAGS})
