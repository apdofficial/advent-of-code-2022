#include <catch2/catch_all.hpp>
#include <array>

#include "day05.hpp"
#include "util.h"
#include "file.hpp"
#include "fmt/color.h"

using namespace aoc::day05;

std::istringstream short_lines_d5_stream{"    [D]           \n"
                                         "[N] [C]           \n"
                                         "[Z] [M] [P]       \n"
                                         " 1   2   3        \n"
                                         "                  \n"
                                         "move 1 from 2 to 1\n"
                                         "move 3 from 1 to 3\n"
                                         "move 2 from 2 to 1\n"
                                         "move 1 from 1 to 2\n"};

auto [short_commands, short_stacks] = parse_input(short_lines_d5_stream);
constexpr std::string_view DATA_PATH = "../../data/day05.txt";

TEST_CASE("Day 05, part 1 test") {
    std::vector<std::vector<char>> stacks(short_stacks);
    for (auto &stack: stacks) {
        std::reverse(stack.begin(), stack.end());
    }
    execute_crane_9000(stacks, short_commands);
    REQUIRE(stacks[0].back() == 'C');
    REQUIRE(stacks[1].back() == 'M');
    REQUIRE(stacks[2].back() == 'Z');
}

TEST_CASE("Day 05, part 2 test") {
    std::vector<std::vector<char>> stacks(short_stacks);
    for (auto &stack: stacks) {
        std::reverse(stack.begin(), stack.end());
    }
    execute_crane_9001(stacks, short_commands);
    REQUIRE(stacks[0].back() == 'M');
    REQUIRE(stacks[1].back() == 'C');
    REQUIRE(stacks[2].back() == 'D');
}

TEST_CASE("Day 05 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto [commands, stacks_] = parse_input(file.istream());
    std::vector<std::vector<char>> stacks{stacks_};
    for (auto &stack: stacks) {
        std::reverse(stack.begin(), stack.end());
    }

    REQUIRE_FALSE(commands.empty());
    REQUIRE_FALSE(stacks.empty());

    std::vector<std::vector<char>> stacks_9000{stacks};
    std::vector<std::vector<char>> stacks_9001{stacks};

    execute_crane_9000(stacks_9000, commands);
    std::array<char, 9> expected_for_9000{'J', 'D', 'T', 'M', 'R', 'W', 'C', 'Q', 'J'};
    for (std::size_t i = 0; i < expected_for_9000.size(); ++i) {
        REQUIRE(expected_for_9000[i] == stacks_9000[i].back());
    }

    execute_crane_9001(stacks_9001, commands);
    std::array<char, 9> expected_for_9001{'V', 'H', 'J', 'D', 'D', 'C', 'W', 'R', 'D'};
    for (std::size_t i = 0; i < expected_for_9001.size(); ++i) {
        REQUIRE(expected_for_9001[i] == stacks_9001[i].back());
    }
}