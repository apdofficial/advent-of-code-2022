#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day14.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day14;

constexpr std::string_view test_input_d14 = R"(
498,4 -> 498,6 -> 496,6
503,4 -> 502,4 -> 502,9 -> 494,9
)";

TEST_CASE("Day 14 test part 1") {
    std::istringstream stream{test_input_d14.data()};
    const auto scan = parse_input(stream, false);
    REQUIRE(part1(scan) == 24);
}

TEST_CASE("Day 14 test part 2") {
    std::istringstream stream{test_input_d14.data()};
    const auto scan = parse_input(stream, false);
    REQUIRE(part2(scan) == 0);
}

TEST_CASE("Day 14 file (correctness)") {
    aoc::File file(file_path);
    REQUIRE(file.is_valid());
    const auto scan = parse_input(file.istream(), false);

    const auto puzzle1 = part1(scan, true);
    fmt::print("Day 13 puzzle 1: {}\n", puzzle1);
    REQUIRE(part1(scan) == 592);

    const auto puzzle2 = part2(scan);
    fmt::print("Day 13 puzzle 2: {}\n", puzzle2);
    // REQUIRE(part1(scan) == 24);
}
