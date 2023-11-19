#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day10.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day10;

std::vector<std::string> short_instruction_d10{{"addx 15"},
                                               {"addx -11"},
                                               {"addx 6"},
                                               {"addx -3"},
                                               {"addx 5"},
                                               {"addx -1"},
                                               {"addx -8"},
                                               {"addx 13"},
                                               {"addx 4"},
                                               {"noop"},
                                               {"addx -1"},
                                               {"addx 5"},
                                               {"addx -1"},
                                               {"addx 5"},
                                               {"addx -1"},
                                               {"addx 5"},
                                               {"addx -1"},
                                               {"addx 5"},
                                               {"addx -1"},
                                               {"addx -35"},
                                               {"addx 1"},
                                               {"addx 24"},
                                               {"addx -19"},
                                               {"addx 1"},
                                               {"addx 16"},
                                               {"addx -11"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx 21"},
                                               {"addx -15"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx -3"},
                                               {"addx 9"},
                                               {"addx 1"},
                                               {"addx -3"},
                                               {"addx 8"},
                                               {"addx 1"},
                                               {"addx 5"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx -36"},
                                               {"noop"},
                                               {"addx 1"},
                                               {"addx 7"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx 2"},
                                               {"addx 6"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx 1"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx 7"},
                                               {"addx 1"},
                                               {"noop"},
                                               {"addx -13"},
                                               {"addx 13"},
                                               {"addx 7"},
                                               {"noop"},
                                               {"addx 1"},
                                               {"addx -33"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx 2"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx 8"},
                                               {"noop"},
                                               {"addx -1"},
                                               {"addx 2"},
                                               {"addx 1"},
                                               {"noop"},
                                               {"addx 17"},
                                               {"addx -9"},
                                               {"addx 1"},
                                               {"addx 1"},
                                               {"addx -3"},
                                               {"addx 11"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx 1"},
                                               {"noop"},
                                               {"addx 1"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx -13"},
                                               {"addx -19"},
                                               {"addx 1"},
                                               {"addx 3"},
                                               {"addx 26"},
                                               {"addx -30"},
                                               {"addx 12"},
                                               {"addx -1"},
                                               {"addx 3"},
                                               {"addx 1"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx -9"},
                                               {"addx 18"},
                                               {"addx 1"},
                                               {"addx 2"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx 9"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx -1"},
                                               {"addx 2"},
                                               {"addx -37"},
                                               {"addx 1"},
                                               {"addx 3"},
                                               {"noop"},
                                               {"addx 15"},
                                               {"addx -21"},
                                               {"addx 22"},
                                               {"addx -6"},
                                               {"addx 1"},
                                               {"noop"},
                                               {"addx 2"},
                                               {"addx 1"},
                                               {"noop"},
                                               {"addx -10"},
                                               {"noop"},
                                               {"noop"},
                                               {"addx 20"},
                                               {"addx 1"},
                                               {"addx 2"},
                                               {"addx 2"},
                                               {"addx -6"},
                                               {"addx -11"},
                                               {"noop"},
                                               {"noop"},
                                               {"noop"}};

constexpr std::string_view DATA_PATH = "../../data/day10.txt";

TEST_CASE("Day 10, part 1 test") {
    auto instructions = parse_input(short_instruction_d10);
    CPU cpu{};
    cpu.process_instructions(instructions);

    auto computed_x_values = cpu.retrieve_register_x_values();
    auto computed_signal_strengths = transform_to_signal_strengths(computed_x_values);

    CapturedRegisterValues expected_x_values{{{20, 21}, {60, 19}, {100, 18}, {140, 21}, {180, 16}, {220, 18}}};
    auto expected_signal_strengths{transform_to_signal_strengths(expected_x_values)};

    REQUIRE(computed_x_values == expected_x_values);

    auto computed_sum = aoc::accumulate(computed_signal_strengths, 0);
    auto expected_sum = aoc::accumulate(expected_signal_strengths, 0);
    REQUIRE(computed_sum == expected_sum);
}

TEST_CASE("Day 10, part 2 test") {
    REQUIRE(false);
}

TEST_CASE("Day 10 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto instructions = parse_input(file.read_lines());
    CPU cpu{};
    cpu.process_instructions(instructions);

    auto computed_x_values = cpu.retrieve_register_x_values();
    auto computed_signal_strengths = transform_to_signal_strengths(computed_x_values);
    auto computed_sum = aoc::accumulate(computed_signal_strengths, 0);
    fmt::println("the computed sum is: {}", computed_sum);
    REQUIRE(computed_sum == 11720);

    REQUIRE(false);
}