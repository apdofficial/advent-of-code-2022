add_library(day1 STATIC)
target_sources(day1
        PRIVATE day1.cpp)
target_include_directories(day1 PUBLIC include)