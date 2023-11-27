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
#include <numeric>

namespace aoc {
    auto map_to_int(std::string_view line) -> std::optional<int>;

    auto map_to_int(char c) -> std::optional<int>;

    auto map_to_ints(std::span<std::string> lines) -> std::vector<std::optional<int>>;

    template<typename Range, typename T = std::ranges::range_value_t<Range>>
    T accumulate(const Range &range, T init) {
        return std::accumulate(std::begin(range), std::end(range), init);
    }

    constexpr auto get_day_file_path(unsigned day) -> std::string {
        return std::string{"../input/day"} + std::to_string(day) + ".txt";
    }
}

