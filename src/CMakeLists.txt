add_subdirectory(day1)

add_executable(advent_of_code_2022)
target_sources(advent_of_code_2022
        PRIVATE
        day2.cpp
        day3.cpp
        day4.cpp
        day5.cpp
        main.cpp
        )

target_link_libraries(advent_of_code_2022
        PRIVATE day1)