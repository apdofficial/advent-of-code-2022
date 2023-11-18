#pragma once

#include <string>
#include <span>
#include <optional>
#include <string_view>
#include <system_error>
#include <array>
#include <charconv>
#include <iostream>
#include <functional>
#include <chrono>

namespace aoc {
    auto map_to_int(std::string_view line) -> std::optional<int>;

    auto map_to_int(char c) -> std::optional<int>;

    auto map_to_ints(std::span<std::string> lines) -> std::vector<std::optional<int>>;
}