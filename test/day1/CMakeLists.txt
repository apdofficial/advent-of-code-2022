add_executable(day1_test)
target_sources(day1_test
        PRIVATE day1.test.cpp)
target_link_libraries(day1_test
        PRIVATE Catch2WithMain
        PRIVATE fmt::fmt
        PRIVATE aoc
)
