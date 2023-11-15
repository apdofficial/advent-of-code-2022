#ifndef ADVENT_OF_CODE_2022_DAY2_HPP
#define ADVENT_OF_CODE_2022_DAY2_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

namespace aoc::day2 {

    auto calculate_strategy_score(const std::vector<std::pair<char, char>> &rounds) -> int;

    auto calculate_new_strategy_score(const std::vector<std::pair<char, char>> &rounds) -> int;
}

#endif //ADVENT_OF_CODE_2022_DAY2_HPP
