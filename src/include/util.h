#pragma once

#include <string>
#include <span>
#include <optional>
#include <string_view>
#include <system_error>
#include <vector>
#include <charconv>
#include <iostream>

namespace aoc
{
    auto stooi(std::string_view line) -> std::optional<int>;

    auto stooi(std::span<const std::string> lines) -> std::vector<std::optional<int>>;
}