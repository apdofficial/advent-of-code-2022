#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day12.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day12;


std::string short_input_d12{"Sabqponm\n"
                            "abcryxxl\n"
                            "accszExk\n"
                            "acctuvwj\n"
                            "abdefghi\n"};

constexpr std::string_view DATA_PATH = "../../data/day12.txt";

TEST_CASE("Day 12, part 1 test") {
    REQUIRE(false);
}

TEST_CASE("Day 12, part 2 test") {
    REQUIRE(false);
}

TEST_CASE("Day 12 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    REQUIRE(false);
}