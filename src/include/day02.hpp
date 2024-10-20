#pragma once

#include <span>

namespace aoc2022::day02 {

    auto calculate_strategy_score(std::span<const std::pair<char, char>> rounds) -> int;

    auto calculate_new_strategy_score(std::span<const std::pair<char, char>> rounds) -> int;
}
