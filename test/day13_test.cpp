#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day13.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day13;

constexpr std::string_view test_input_d13 = R"([1,1,3,1,1]
[1,1,5,1,1]

[[1],[2,3,4]]
[[1],4]

[9]
[[8,7,6]]

[[4,4],4,4]
[[4,4],4,4,4]

[7,7,7,7]
[7,7,7]

[]
[3]

[[[]]]
[[]]

[1,[2,[3,[4,[5,6,7]]]],8,9]
[1,[2,[3,[4,[5,6,0]]]],8,9])";

SCENARIO("Day 13") {
    GIVEN("test input") {
        std::istringstream stream{test_input_d13.data()};
        const auto packets = parse_input(stream);
        THEN("puzzle 1 is solved") {
            REQUIRE(part1(packets) == 13);
        }
        THEN("puzzle 2 is solved") {
            REQUIRE(part2(packets) == 140);
        }
    }
    GIVEN("file input") {
        aoc::File file(file_path);
        THEN("file is valid") {
            REQUIRE(file.is_valid());
        }
        const auto packets = parse_input(file.istream());
        THEN("puzzle 1 is solved") {
            auto puzzle1 = part1(packets);
            fmt::print("Day 13 puzzle 1: {}\n", puzzle1);
            REQUIRE(puzzle1 == 5684);
        }
        THEN("puzzle 2 is solved") {
            auto puzzle2 = part2(packets);
            fmt::print("Day 13 puzzle 2: {}\n", puzzle2);
            REQUIRE(puzzle2== 22932);
        }
    }
}
