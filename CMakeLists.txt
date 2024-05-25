cmake_minimum_required(VERSION 3.20)

project(hexcode)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -g -O0)
    if(LINUX)
        add_compile_options(-fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    endif()
endif()

add_executable(hexcode hexcode.c data.c)
