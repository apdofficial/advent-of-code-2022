cmake_minimum_required(VERSION 3.24)
project(advent_of_code_2022)

set(CMAKE_CXX_STANDARD 20)

add_executable(advent_of_code_2022 day1/day1.cpp day2/day2.cpp main.cpp day1/day1.h day2/day2.h day3/day3.cpp day3/day3.h Google_tests/test.cpp Google_tests/test.cpp day4/day4.cpp day4/day4.h day5/day5.cpp day5/day5.h)

find_package(Boost 1.80.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(Google_tests)