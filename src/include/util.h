#pragma once

#include <string>
#include <optional>
#include <chrono>
#include <numeric>
#include <format>
#include <span>

namespace aoc {
    auto map_to_int(std::string_view line) -> std::optional<int>;

    auto map_to_int(char c) -> std::optional<int>;

    auto map_to_ints(std::span<std::string> lines) -> std::vector<std::optional<int>>;

    template<typename Range, typename T = std::ranges::range_value_t<Range>>
    T accumulate(const Range &range, T init) {
        return std::accumulate(std::begin(range), std::end(range), init);
    }

    auto inline get_day_file_path(const unsigned day) -> std::string {
        return std::format("../../data/day{}.txt", day);
    }
}

