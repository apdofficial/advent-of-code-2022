#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <array>

#include "day1.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day1;

std::vector<std::string> short_lines{"1000", "2000", "3000", "",
                                     "4000", "",
                                     "5000", "6000", "",
                                     "7000", "8000", "9000","",
                                     "10000"};
auto short_calories{aoc::map_to_ints(short_lines)};

constexpr std::string_view DATA_PATH = "../../data/day1.txt";

TEST_CASE("Day 1, part 1 test") {
    auto result = top_1_elf_calories(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 24000);
}

TEST_CASE("Day 1, part 2 test") {
    auto result = top_3_elf_calories(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 45000);
}

TEST_CASE("Day 1 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto lines = file.read_lines();
    REQUIRE_FALSE(lines.empty());

    auto calories = aoc::map_to_ints(lines);

    auto result1 = top_1_elf_calories(calories);
    REQUIRE(result1.has_value());
    REQUIRE(result1.value() == 69693);

    auto result2 = top_3_elf_calories(calories);
    REQUIRE(result2.has_value());
    REQUIRE(result2.value() == 200945);
}