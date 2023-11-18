#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day9.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day9;

std::vector<std::string> short_motions_d8{{"R 4"},
                                          {"U 4"},
                                          {"L 3"},
                                          {"D 1"},
                                          {"R 4"},
                                          {"D 1"},
                                          {"L 5"},
                                          {"R 2"}};
constexpr std::string_view DATA_PATH = "../../data/day9.txt";


TEST_CASE("Day 9, part 1 test") {
    auto rope_motions = parse_input(short_motions_d8);
    auto simulation = simulate_rope(rope_motions);
    REQUIRE(simulation.tail_visited().size() == 13);
}

TEST_CASE("Day 9, part 2 test") {
    REQUIRE(false);
}

TEST_CASE("Day 9 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto rope_motions = parse_input(file.read_lines());
    auto simulation = simulate_rope(rope_motions);
    fmt::println("tail visited {} position(s) at least once.", simulation.tail_visited().size());
    REQUIRE(simulation.tail_visited().size() == 6494);
}