#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <array>

#include "day02.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day02;

std::vector<std::pair<char, char>> short_rounds{{'A', 'Y'},
                                                {'B', 'X'},
                                                {'C', 'Z'}};

constexpr std::string_view DATA_PATH = "../../data/day02.txt";

TEST_CASE("Day 02, part 1 test") {
    REQUIRE(15 == calculate_strategy_score(short_rounds));
}

TEST_CASE("Day 02, part 2 test") {
    REQUIRE(12 == calculate_new_strategy_score(short_rounds));
}

TEST_CASE("Day 02 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto rounds = file.read_pairs();
    REQUIRE_FALSE(rounds.empty());

    REQUIRE(13526 == calculate_strategy_score(rounds));
    REQUIRE(14204 == calculate_new_strategy_score(rounds));
}