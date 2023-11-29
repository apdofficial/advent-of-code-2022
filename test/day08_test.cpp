#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <iostream>
#include "day08.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day08;

Forest short_forest_d8{{{3, 0, 3, 7, 3},
                        {2, 5, 5, 1, 2},
                        {6, 5, 3, 3, 2},
                        {3, 3, 5, 4, 9},
                        {3, 5, 3, 9, 0}}};

constexpr std::string_view DATA_PATH = "../../data/day08.txt";


TEST_CASE("Day 08, part 1 test") {
    REQUIRE(count_visible_trees(short_forest_d8) == 21);
}

TEST_CASE("Day 08, part 2 test") {
    REQUIRE(calculate_scenic_score(short_forest_d8, {1, 2, 0}) == 4);
    REQUIRE(calculate_scenic_score(short_forest_d8, {3, 2, 0}) == 8);
    const auto scenic_tree = find_tree_with_highest_scenic_score(short_forest_d8);
    REQUIRE(scenic_tree.scenic_score == 8);
}

TEST_CASE("Day 08 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto forest = file.read_matrix();
    auto visible_trees_num = count_visible_trees(forest);
    fmt::println("visible_trees_num: {}", visible_trees_num);
    REQUIRE(visible_trees_num == 1717);

    const auto scenic_tree = find_tree_with_highest_scenic_score(forest);
    std::cout << "scenic_tree: " << scenic_tree;
    REQUIRE(scenic_tree.scenic_score == 321975);
}