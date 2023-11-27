add_library(aoc STATIC)

# Check if we have Boost
find_package(Boost 1.74.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(aoc ${Boost_LIBRARIES})
endif()

target_link_libraries(aoc PRIVATE fmt::fmt)

target_sources(aoc PRIVATE
        day01.cpp
        day02.cpp
        day03.cpp
        day04.cpp
        day05.cpp
        day06.cpp
        day07.cpp
        day08.cpp
        day09.cpp
        day10.cpp
        day11.cpp
        day12.cpp
        day13.cpp
        util.cpp
        file.cpp
)

target_include_directories(aoc PUBLIC include)