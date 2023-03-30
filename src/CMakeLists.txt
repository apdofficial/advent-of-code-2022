add_library(aoc STATIC)

target_sources(aoc PRIVATE
        Day1.cpp
        day2.cpp
        day3.cpp
        day4.cpp
        day5.cpp
        util.cpp
        DayLineSubject.cpp
        FileDayProvider.cpp
        NetworkDayProvider.cpp
        File.cpp
)

target_include_directories(aoc PUBLIC include)