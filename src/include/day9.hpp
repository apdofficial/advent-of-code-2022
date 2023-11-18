#pragma once

#include <algorithm>
#include <ranges>
#include <string>

#include "util.h"

namespace aoc::day9 {
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    using Magnitude = unsigned;
    using Motion = std::pair<Direction, Magnitude>;

    namespace details {
        auto map_to_direction(char c) -> std::optional<Direction>;

         // we consume the string so we want pass by value
        auto map_to_motion(const std::pair<char, char>& raw_motion) -> std::optional<Motion>;
    }

    auto parse_input(const std::vector<std::pair<char, char>> &raw_motions) -> std::vector<Motion>;

    auto count_tail_positions(const std::vector<Motion>& motions) -> unsigned;

}