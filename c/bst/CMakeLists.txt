project(bst LANGUAGES C)
cmake_minimum_required(VERSION 3.10)

add_compile_options(-Wall -Wextra -pedantic -Werror)
add_executable(simple
    simple.c
    )
