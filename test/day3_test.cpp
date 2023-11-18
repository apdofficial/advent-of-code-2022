#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <array>

#include "day3.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day3;

std::vector<std::string> short_list{"vJrwpWtwJgWrhcsFMMfFFhFp",
                                    "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
                                    "PmmdzqPrVvPwwTWBwg",
                                    "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
                                    "ttgJtRGJQctTZtZT",
                                    "CrZsJsPPZsGzwwsLwLmpwMDw"};

constexpr std::string_view DATA_PATH = "../../data/day3.txt";

TEST_CASE("Day 3, part 1 test") {
    REQUIRE(157 == sum_item_priorities_of_both_compartments(short_list));
}

TEST_CASE("Day 3, part 2 test") {
    REQUIRE(70 == sum_grouped_item_priorities_of_both_compartments(short_list));
}

TEST_CASE("Day 3 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto list = file.read_lines();
    REQUIRE_FALSE(list.empty());

    REQUIRE(7917 == sum_item_priorities_of_both_compartments(list));
    REQUIRE(2585 == sum_grouped_item_priorities_of_both_compartments(list));
}