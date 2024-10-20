add_executable(tests)

target_link_libraries(tests
        PRIVATE Catch2WithMain
        PRIVATE fmt::fmt
        PRIVATE libaoc2022
)

target_sources(tests PRIVATE
        day01_test.cpp
        # day02_test.cpp
        # day03_test.cpp
        # day04_test.cpp
        # day05_test.cpp
        # day06_test.cpp
        # day07_test.cpp
        # day08_test.cpp
        # day09_test.cpp
        # day10_test.cpp
        # day11_test.cpp
        # day12_test.cpp
        # day13_test.cpp
        # day14_test.cpp
        # day15_test.cpp
)
