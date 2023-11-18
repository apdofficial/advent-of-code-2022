#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <array>

#include "day4.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day4;

std::vector<std::string> short_lines_d4{"2-4,6-8",
                                      "2-3,4-5",
                                      "5-7,7-9",
                                      "2-8,3-7",
                                      "6-6,4-6",
                                      "2-6,4-8"};

auto short_ranges = map_to_ranges(short_lines_d4);

constexpr std::string_view DATA_PATH = "../../data/day4.txt";

TEST_CASE("Day 4, part 1 test") {
    REQUIRE(2 == num_of_fully_contained_ranges(short_ranges));
}

TEST_CASE("Day 4, part 2 test") {
    REQUIRE(4 == num_of_overlapping_ranges(short_ranges));
}

TEST_CASE("Day 4 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto lines = file.read_lines();
    auto ranges = map_to_ranges(lines);
    REQUIRE_FALSE(ranges.empty());

    REQUIRE(651 == num_of_fully_contained_ranges(ranges));
    REQUIRE(956 == num_of_overlapping_ranges(ranges));
}