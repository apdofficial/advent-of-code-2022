#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day13.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day13;


std::vector<std::string> short_input_d13{"[1,1,3,1,1]",
                                         "[1,1,5,1,1]",
                                         "",
                                         "[[1],[2,3,4]]",
                                         "[[1],4]",
                                         "",
                                         "[9]",
                                         "[[8,7,6]]",
                                         "",
                                         "[[4,4],4,4]",
                                         "[[4,4],4,4,4]",
                                         "",
                                         "[7,7,7,7]",
                                         "[7,7,7]",
                                         "",
                                         "[]",
                                         "[3]",
                                         "",
                                         "[[[]]]",
                                         "[[]]",
                                         "",
                                         "[1,[2,[3,[4,[5,6,7]]]],8,9]",
                                         "[1,[2,[3,[4,[5,6,0]]]],8,9]"};

constexpr std::string_view DATA_PATH = "../../data/day13.txt";

TEST_CASE("Day 13, part 1 test") {
    auto packets = parse_input(short_input_d13);
    REQUIRE(part1(packets) == 13);
}

TEST_CASE("Day 13, part 2 test") {
    REQUIRE(false);
}

TEST_CASE("Day 13 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    REQUIRE(false);
}