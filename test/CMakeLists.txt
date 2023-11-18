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
)
target_link_libraries(tests
        PRIVATE Catch2WithMain
        PRIVATE fmt::fmt
        PRIVATE aoc
)