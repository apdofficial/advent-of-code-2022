#pragma once

#include <numeric>
#include <optional>
#include <span>
#include <string>

namespace aoc2022 {

auto map_to_int(std::string_view line) -> std::optional<int>;

auto map_to_int(char c) -> std::optional<int>;

auto map_to_ints(std::span<std::string> lines)
    -> std::vector<std::optional<int>>;

auto map(std::span<std::string> lines) -> std::vector<int>;

template <typename Range,
          typename T = std::ranges::range_value_t<Range>,
          typename Op>
T accumulate(const Range& range, T init, Op op) {
  return std::accumulate(std::begin(range), std::end(range), init, op);
}

template <typename Range, typename T = std::ranges::range_value_t<Range>>
T accumulate(const Range& range, T init) {
  return std::accumulate(std::begin(range), std::end(range), init);
}

}  // namespace aoc2022
