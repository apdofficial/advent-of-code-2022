#pragma once

#include <cstdlib>
#include <span>
#include <string>
#include <optional>
#include <numeric>

namespace aoc::day01 {

    auto top_1_elf_calories(std::span<std::optional<int>> calories) -> std::optional<int>;

    auto top_3_elf_calories(std::span<std::optional<int>> calories) -> std::optional<int>;
}




