#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

namespace aoc::day3 {

    auto sum_item_priorities_of_both_compartments(const std::vector<std::string>& lines) -> int;

    auto sum_grouped_item_priorities_of_both_compartments(const std::vector<std::string>& lines) -> int;
}