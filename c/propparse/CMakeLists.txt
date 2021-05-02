cmake_minimum_required(VERSION 3.3)
project(propparse VERSION 1.0.0 LANGUAGES C)

include(CheckSymbolExists)

check_symbol_exists(getline "stdio.h" HAVE_GETLINE)

if (NOT ${HAVE_GETLINE})
    message(FATAL_ERROR "getline() not found")
endif()

list(APPEND propparse_srcs
    main.c
    property.c
    )

add_executable(propparse ${propparse_srcs})
