#pragma once

#include <string>
#include <span>
#include <optional>
#include <string_view>
#include <system_error>
#include <array>
#include <charconv>
#include <iostream>

namespace aoc
{
    constexpr auto stooi(std::string_view line) -> std::optional<int>;

    auto stooi(std::span<std::string> lines) -> std::vector<std::optional<int>>;

    auto measure_average_runtime(const std::function<void()>& fn, std::size_t n_runs) -> std::chrono::milliseconds;
}