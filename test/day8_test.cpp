#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day8.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day8;

Forest short_forest_d8{{{3, 0, 3, 7, 3},
                        {2, 5, 5, 1, 2},
                        {6, 5, 3, 3, 2},
                        {3, 3, 5, 4, 9},
                        {3, 5, 3, 9, 0}}};

constexpr std::string_view DATA_PATH = "../../data/day8.txt";


TEST_CASE("Day 8, part 1 test") {
    auto visible_trees = count_visible_trees(short_forest_d8);
    REQUIRE(visible_trees == 21);
}

TEST_CASE("Day 8, part 2 test") {
    REQUIRE(false);
}

TEST_CASE("Day 8 file (correctness)") {
    REQUIRE(false);
}