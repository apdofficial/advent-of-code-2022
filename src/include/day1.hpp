#pragma once

#include <charconv>
#include <cstdlib>
#include <span>
#include <optional>
#include <string>

namespace aoc::day1{
    auto top_1_elf_calories(std::span<std::optional<int>> calories) -> std::optional<int>;

    auto top_3_elf_calories_inplace(std::span<std::optional<int>> calories) -> std::optional<int>;

    auto top_3_elf_calories_bubble(std::span<std::optional<int>> calories) -> std::optional<int>;

    auto top_3_elf_calories_quick(std::span<std::optional<int>> calories) -> std::optional<int>;

    void run(std::string_view file_path);
}

