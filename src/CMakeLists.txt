add_library(aoc STATIC)

# Check if we have Boost
find_package(Boost 1.74.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(aoc ${Boost_LIBRARIES})
endif()

target_link_libraries(aoc PRIVATE fmt::fmt)

target_sources(aoc PRIVATE
        day1.cpp
        day2.cpp
        day3.cpp
        day4.cpp
        day5.cpp
        day6.cpp
        day7.cpp
        day8.cpp
        day9.cpp
        day10.cpp
        day11.cpp
        day12.cpp
        util.cpp
        file.cpp
)

target_include_directories(aoc PUBLIC include)