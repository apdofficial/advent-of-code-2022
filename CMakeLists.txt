cmake_minimum_required(VERSION 3.22)
project(aoc2022)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(--std=c++20)

add_executable(aoc2022 main.cpp)

find_package(Boost REQUIRED system program_options)
SET(Boost_USE_MULTITHREAD ON)
set(Boost_USE_STATIC_LIBS ON)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(asio INTERFACE ${boost_asio_SOURCE_DIR}/include)

target_link_libraries(aoc2022
        PRIVATE fmt::fmt
        PRIVATE libaoc2022
        PRIVATE Boost::program_options
)

add_subdirectory(ext)
add_subdirectory(test)
add_subdirectory(src)
