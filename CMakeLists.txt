cmake_minimum_required(VERSION 3.22)
project(advent_of_code_2022)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(--std=c++20)

add_subdirectory(ext)
add_subdirectory(test)
add_subdirectory(src)