#include <catch2/catch_all.hpp>
#include "aoc.hpp"
#include "day1.hpp"

std::vector<std::string> short_lines {
                                "1000", "2000", "3000", "",
                                "4000", "",
                                "5000", "6000", "",
                                "7000", "8000", "9000", "",
                                "10000"};
std::vector<std::optional<int>> short_calories {aoc::map_to_int(short_lines) };

constexpr std::string_view DATA_PATH = "/Users/andrejpistek/Developer/GitHub/advent-of-code-2022/data/data1.txt";

TEST_CASE("Day 1, part 1 test") {
    auto result = aoc::day1::top_1_elf_calories(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 24000);
}

TEST_CASE("Day 1, part 2 test (Quick Sort)") {
    auto result = aoc::day1::top_3_elf_calories_quick(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 45000);
}

TEST_CASE("Day 1, part 2 test (Bubble Sort)") {
    auto result = aoc::day1::top_3_elf_calories_bubble(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 45000);
}

TEST_CASE("Day 1, part 2 test (Inplace)") {
    auto result = aoc::day1::top_3_elf_calories_inplace(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 45000);
}

TEST_CASE("Day 1 file") {
    auto file = aoc::File(DATA_PATH);
    REQUIRE(file.is_valid());

    auto lines = file.read_lines();
    REQUIRE_FALSE(lines.empty());

    auto calories = aoc::map_to_int(lines);

    auto result1 = aoc::day1::top_1_elf_calories(calories);
    REQUIRE(result1.has_value());
    REQUIRE(result1.value() == 69693);

    auto result2 = aoc::day1::top_3_elf_calories_quick(calories);
    REQUIRE(result2.has_value());
    REQUIRE(result2.value() == 200945);

    auto result3 = aoc::day1::top_3_elf_calories_bubble(calories);
    REQUIRE(result3.has_value());
    REQUIRE(result3.value() == 200945);

    auto result4 = aoc::day1::top_3_elf_calories_inplace(calories);
    REQUIRE(result4.has_value());
    REQUIRE(result4.value() == 200945);
}