#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day9.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day9;

std::vector<std::string> short_motions1_d8{{"R 4"},
                                           {"U 4"},
                                           {"L 3"},
                                           {"D 1"},
                                           {"R 4"},
                                           {"D 1"},
                                           {"L 5"},
                                           {"R 2"}};

std::vector<std::string> short_motions2_d8{{"R 5"},
                                           {"U 8"},
                                           {"L 8"},
                                           {"D 3"},
                                           {"R 17"},
                                           {"D 10"},
                                           {"L 25"},
                                           {"U 20"}};

constexpr std::string_view DATA_PATH = "../../data/day9.txt";


TEST_CASE("Day 9, part 1 test") {
    auto rope_motions = parse_input(short_motions1_d8);
    auto simulation = simulate_rope(rope_motions, 2).value();
    REQUIRE(simulation.tail_visited().size() == 13);
}



TEST_CASE("Day 9, part 2 test") {
    auto rope_motions = parse_input(short_motions2_d8);
    auto simulation = simulate_rope(rope_motions, 10).value();
    REQUIRE(simulation.tail_visited().size() == 36);
}

TEST_CASE("Day 9 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto rope_motions = parse_input(file.read_lines());
    auto simulation_short = simulate_rope(rope_motions, 2).value();
    fmt::println("tail visited {} position(s) at least once in the simulation_short.", simulation_short.tail_visited().size());
    REQUIRE(simulation_short.tail_visited().size() == 6494);

    auto simulation_long = simulate_rope(rope_motions, 10).value();
    fmt::println("tail visited {} position(s) at least once in the simulation_long.", simulation_long.tail_visited().size());
    REQUIRE(simulation_long.tail_visited().size() == 2691);
}