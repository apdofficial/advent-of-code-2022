add_library(libaoc2022 STATIC)

find_package(Boost 1.85.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(libaoc2022 PRIVATE ${Boost_LIBRARIES})
endif()

target_link_libraries(libaoc2022 PRIVATE fmt::fmt)

target_include_directories(libaoc2022 PUBLIC include)

target_sources(libaoc2022 PRIVATE
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
        day14.cpp
        day15.cpp
        file_puzzle_reader.cpp
        util.cpp
)

