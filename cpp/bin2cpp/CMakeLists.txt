cmake_minimum_required(VERSION 3.12)
project(bin2cpp VERSION 1.0.0)

find_program(GIT_CMD git)
find_program(DATE_CMD date)

add_executable(bin2cpp main.cpp)

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

    target_compile_definitions(bin2cpp PRIVATE GIT_REV="${GIT_REV}")
    target_compile_definitions(bin2cpp PRIVATE GIT_BRANCH="${GIT_BRANCH}")
endif()

if (DATE_CMD) 
    execute_process(
        COMMAND ${DATE_CMD} --rfc-3339=seconds
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE DATE_OUTPUT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    target_compile_definitions(bin2cpp PRIVATE BUILDTIME="${DATE_OUTPUT}")
endif()

target_compile_definitions(bin2cpp PRIVATE APP_VERSION="${CMAKE_PROJECT_VERSION}")

install(TARGETS bin2cpp)
