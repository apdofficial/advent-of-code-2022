#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day15.hpp"
#include "file.hpp"

using namespace aoc2022::day15;

constexpr std::string_view test_input_d15 = R"(
Sensor at x=2, y=18: closest beacon is at x=-2, y=15
Sensor at x=9, y=16: closest beacon is at x=10, y=16
Sensor at x=13, y=2: closest beacon is at x=15, y=3
Sensor at x=12, y=14: closest beacon is at x=10, y=16
Sensor at x=10, y=20: closest beacon is at x=10, y=16
Sensor at x=14, y=17: closest beacon is at x=10, y=16
Sensor at x=8, y=7: closest beacon is at x=2, y=10
Sensor at x=2, y=0: closest beacon is at x=2, y=10
Sensor at x=0, y=11: closest beacon is at x=2, y=10
Sensor at x=20, y=14: closest beacon is at x=25, y=17
Sensor at x=17, y=20: closest beacon is at x=21, y=22
Sensor at x=16, y=7: closest beacon is at x=15, y=3
Sensor at x=14, y=3: closest beacon is at x=15, y=3
Sensor at x=20, y=1: closest beacon is at x=15, y=3
)";

TEST_CASE("Day 15 test part 1") {
    std::istringstream stream{test_input_d15.data()};
    const auto scan = load_input(stream);
    REQUIRE(part1(scan, 10) == 26);
}

TEST_CASE("Day 15 test part 2") {
    std::istringstream stream{test_input_d15.data()};
    const auto scan = load_input(stream);
    REQUIRE(part2(scan, 20) == 56000011);
}

TEST_CASE("Day 15 file (correctness)") {
    aoc2022::File file(file_path);
    REQUIRE(file.is_valid());
    const auto scan = load_input(file.istream());
    const auto puzzle1 = part1(scan, 2000000L);
    fmt::print("Day 15 puzzle 1: {}\n", puzzle1);
    REQUIRE(puzzle1 == 6275922);
    // const auto puzzle2 = part2(scan, 4000000L);
    // fmt::print("Day 15 puzzle 2: {}\n", puzzle2);
    // REQUIRE(puzzle2 == 11747175442119);
}
