#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <numeric>
#include <span>

namespace aoc::day2 {

    auto calculate_strategy_score(std::span<const std::pair<char, char>> rounds) -> int;

    auto calculate_new_strategy_score(std::span<const std::pair<char, char>> rounds) -> int;
}