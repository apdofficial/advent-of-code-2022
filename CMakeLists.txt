cmake_minimum_required(VERSION 3.24)
project(advent_of_code_2022)

set(CMAKE_CXX_STANDARD 20)

add_executable(advent_of_code_2022 day1/day1.cpp day2/day2.cpp main.cpp day1/day1.h day2/day2.h)