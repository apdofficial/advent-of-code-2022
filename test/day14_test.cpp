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

SCENARIO("Day 14") {
    GIVEN("test input") {
        std::istringstream stream{test_input_d14.data()};
        const auto scan = parse_input(stream);
        THEN("puzzle 1 is solved") {
            REQUIRE(part1(scan) == -1);
        }
        THEN("puzzle 2 is solved") {
            REQUIRE(part2(scan) == -1);
        }
    }
    GIVEN("file input") {
        aoc::File file(file_path);
        THEN("file is valid") {
            REQUIRE(file.is_valid());
        }
        const auto scan = parse_input(file.istream());
        THEN("puzzle 1 is solved") {
            auto puzzle1 = part1(scan);
            fmt::print("Day 14 puzzle 1: {}\n", puzzle1);
            REQUIRE(puzzle1 == -1);
        }
        THEN("puzzle 2 is solved") {
            auto puzzle2 = part2(scan);
            fmt::print("Day 14 puzzle 2: {}\n", puzzle2);
            REQUIRE(puzzle2== -1);
        }
    }
}
