cmake_minimum_required(VERSION 3.22)
project(aoc2022)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(--std=c++20)

add_executable(aoc2022 main.cpp)
target_link_libraries(aoc2022
        PRIVATE Catch2WithMain
        PRIVATE fmt::fmt
        PRIVATE aoc
)

add_subdirectory(ext)
add_subdirectory(test)
add_subdirectory(src)

