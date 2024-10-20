#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <span>

namespace aoc2022::day03 {

    auto sum_item_priorities_of_both_compartments(std::span<const std::string> lines) -> int;

    auto sum_grouped_item_priorities_of_both_compartments(std::span<const std::string> lines) -> int;
}
