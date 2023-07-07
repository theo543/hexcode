cmake_minimum_required(VERSION 3.20)

project(hexcode)

set(CMAKE_CXX_STANDARD 20)

add_executable(hexcode src/hexcode.cpp data/codes.inc data/official_names.inc)
target_include_directories(hexcode PRIVATE data)

