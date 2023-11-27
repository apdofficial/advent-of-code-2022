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

TEST_CASE("Day 13, part 1 test") {
    std::istringstream stream{test_input_d13.data()};
    auto packets = parse_input(stream);
    REQUIRE(part1(packets) == 13);
}

TEST_CASE("Day 13, part 2 test") {
    std::istringstream stream{test_input_d13.data()};
    auto packets = parse_input(stream);
    REQUIRE(part2(packets) == 0);
}

TEST_CASE("Day 13") {
    aoc::File file(file_path);
    REQUIRE(file.is_valid());

    auto packets = parse_input(file.istream());

    auto answer1 = part1(packets);
    fmt::println("Answer 1: {}", answer1);
    auto answer2 = part2(packets);
    fmt::println("Answer 2: {}", answer2);
}