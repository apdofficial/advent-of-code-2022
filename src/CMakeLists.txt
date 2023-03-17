add_library(aoc STATIC)

target_sources(aoc PRIVATE
        day1.cpp
        day2.cpp
        day3.cpp
        day4.cpp
        day5.cpp
        ../main.cpp
        aoc.cpp
)

target_include_directories(aoc PUBLIC include)