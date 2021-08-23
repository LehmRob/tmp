cmake_minimum_required(VERSION 3.12)
project(bin2cpp VERSION 1.0.0)

find_program(GIT_CMD git)

if (GIT_CMD)
    execute_process(
        COMMAND ${GIT_CMD} rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )

    execute_process(
        COMMAND ${GIT_CMD} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_REV
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )
else()
    set(GIT_BRANCH "unknown")
    set(GIT_REV "")
endif()

find_program(DATE_CMD date)

if (DATE_CMD) 
    execute_process(
        COMMAND ${DATE_CMD} --rfc-3339=seconds -u
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE BUILDTIME
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )
else()
    set(BUILDTIME "")
endif()

configure_file(config.h.in config.h)

add_executable(bin2cpp main.cpp)
target_include_directories(bin2cpp PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
install(TARGETS bin2cpp)
