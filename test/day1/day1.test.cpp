#include <catch2/catch_all.hpp>
#include <day1/day1.hpp>
#include <fmt/core.h>

std::vector<std::string> lines{"1000", "2000", "3000", "",
                               "4000", "",
                               "5000", "6000", "",
                               "7000", "8000", "9000", "",
                               "10000"};

TEST_CASE("Day 1, part 1 test") {
    auto calories = top_1_elf_calories(lines);
    REQUIRE(calories.has_value());
    REQUIRE(calories.value() == 24000);
}

TEST_CASE("Day 1, part 2 test") {
//    TODO: implement top_3_elf_calories
//    auto calories = top_3_elf_calories(lines);
//    REQUIRE(calories.has_value());
//    REQUIRE(calories.value() == 45000);
}