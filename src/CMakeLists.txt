add_library(aoc STATIC)

target_sources(aoc PRIVATE
        day1.cpp
        day2.cpp
        day3.cpp
        day4.cpp
        day5.cpp
        day6.cpp
        day7.cpp
        util.cpp
        file.cpp
)

target_include_directories(aoc PUBLIC include)