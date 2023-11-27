add_executable(tests)
target_sources(tests PRIVATE
        day1_test.cpp
        day2_test.cpp
        day3_test.cpp
        day4_test.cpp
        day5_test.cpp
        day6_test.cpp
        day7_test.cpp
        day8_test.cpp
        day9_test.cpp
        day10_test.cpp
        day11_test.cpp
        day12_test.cpp
)
target_link_libraries(tests
        PRIVATE Catch2WithMain
        PRIVATE fmt::fmt
        PRIVATE aoc
)

# Check if we have Boost
find_package(Boost 1.74.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(tests ${Boost_LIBRARIES})
endif()