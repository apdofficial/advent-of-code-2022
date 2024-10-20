#pragma once

#include <algorithm>
#include <fmt/core.h>
#include <numeric>
#include <ranges>
#include <set>
#include <string>
#include <vector>

namespace aoc2022 {
using InputLines = std::vector<std::string>;

/**
 * @brief Half open interval [start, end)
 */
struct Range {
  long start;
  long end;

  auto friend operator==(const Range &lhs, const Range &rhs) -> bool {
    return rhs.start == lhs.start && rhs.end == lhs.end;
  }

  auto friend operator!=(const Range &lhs, const Range &rhs) -> bool {
    return !(rhs == lhs);
  }

  auto friend operator<=>(const Range &lhs, const Range &rhs) {
    if (lhs.start < rhs.start)
      return std::strong_ordering::less;
    if (lhs.start > rhs.start)
      return std::strong_ordering::greater;
    if (lhs.end < rhs.end)
      return std::strong_ordering::less;
    if (lhs.end > rhs.end)
      return std::strong_ordering::greater;
    return std::strong_ordering::equal;
  }

  [[nodiscard]] auto size() const -> long { return end - start; }

  [[nodiscard]] auto contains(const long value) const -> bool {
    return start <= value && value < end;
  }

  [[nodiscard]] auto is_sub_range(const Range &rhs) const -> bool {
    return start >= rhs.start && end <= rhs.end;
  }

  [[nodiscard]] auto intersects(const Range &rhs) const -> bool {
    return start < rhs.end && end > rhs.start;
  }

  [[nodiscard]] auto is_adjacent(const Range &rhs) const -> bool {
    return start == rhs.end || end == rhs.start;
  }

  [[nodiscard]] auto merge_if_adjacent_or_overlapping(const Range &rhs) const
      -> std::optional<Range> {
    if ((intersects(rhs) || is_adjacent(rhs)) && *this != rhs) {
      return Range{.start = std::min(start, rhs.start),
                   .end = std::max(end, rhs.end)};
    }
    return std::nullopt;
  }
};

struct RangeSet {

  void insert(const Range &new_range) {
    if (!merge(new_range)) {
      ranges_.insert(new_range);
    }
  }

  void erase(const Range &range) { ranges_.erase(range); }

  [[nodiscard]] auto ranges() const -> std::set<Range> { return ranges_; }

  [[nodiscard]] auto count_values() const -> size_t {
    return std::accumulate(ranges_.begin(), ranges_.end(), 0,
                           [](const auto &acc, const auto &range) {
                             return acc + std::abs(range.end - range.start);
                           });
  }

  [[nodiscard]] auto contains(const long col) const -> bool {
    return std::ranges::any_of(
        ranges_, [col](const auto &range) { return range.contains(col); });
  }

private:
  auto merge(const Range &new_range) -> bool {
    for (auto range : ranges_) {
      if (const auto merged_range =
              range.merge_if_adjacent_or_overlapping(new_range)) {
        ranges_.erase(range);
        ranges_.insert(*merged_range);
        merge(*merged_range);
        return true;
      }
    }
    return false;
  }

  std::set<Range> ranges_{};
};

struct Coordinates {
  int row{0};
  int col{0};

  Coordinates(){}
  
  Coordinates(int row_, int col_): row(row_), col(col_){}

  bool operator!=(const Coordinates &rhs) const {
    return col != rhs.col || row != rhs.row;
  }
  bool operator==(const Coordinates &rhs) const {
    return col == rhs.col && row == rhs.row;
  }

  friend auto operator+(const Coordinates &lhs, const Coordinates &rhs)
      -> Coordinates {
    return {lhs.row + rhs.row, lhs.col + rhs.col};
  }

  friend auto operator-(const Coordinates &lhs, const Coordinates &rhs)
      -> Coordinates {
    return {lhs.row - rhs.row, lhs.col - rhs.col};
  }
};

struct BoundingBox {
  int min_row = 0;
  int max_row = 0;
  int min_col = 0;
  int max_col = 0;

  void update(const Coordinates &coord) {
    min_row = std::min(min_row, coord.row);
    max_row = std::max(max_row, coord.row);
    min_col = std::min(min_col, coord.col);
    max_col = std::max(max_col, coord.col);
  }
};

template <typename T>
struct Map {
  explicit Map(unsigned long long width, unsigned long long height, T init,
               bool include_negative = false)
      : include_negative_(include_negative),
        width_(width * (include_negative ? 2 : 1)),
        height_(height * (include_negative ? 2 : 1)),
        center_(include_negative ? height : 0,
                include_negative ? width : 0),
        map(height_, std::vector(width_, init)) {}

  [[nodiscard]] auto at(long long row, long long col) const -> auto & {
    return map[map_row_to_internal(row)][map_col_to_internal(col)];
  }

  [[nodiscard]] auto at(long long row, long long col) -> auto & {
    return map[map_row_to_internal(row)][map_col_to_internal(col)];
  }

  [[nodiscard]] auto operator[](const Coordinates &crd) const -> auto & {
    return map[map_row_to_internal(crd.row)][map_col_to_internal(crd.col)];
  }

  [[nodiscard]] auto operator[](const Coordinates &crd) -> auto & {
    return map[map_row_to_internal(crd.row)][map_col_to_internal(crd.col)];
  }

  [[nodiscard]] auto begin() const { return map.begin(); }
  [[nodiscard]] auto end() const { return map.end(); }

  [[nodiscard]] auto iota_rows() const {
    auto split = height_ / 2;
    return std::views::iota(include_negative_ ? -split : 0,
                            include_negative_ ? split : height_);
  }
  [[nodiscard]] auto iota_cols() const {
    auto split = width_ / 2;
    return std::views::iota(include_negative_ ? -split : 0,
                            include_negative_ ? split : width_);
  }

private:
  [[nodiscard]] auto rows() const { return map.size(); }
  [[nodiscard]] auto cols() const { return map[0].size(); }

  [[nodiscard]] auto map_row_to_internal(long long row) const -> long long {
    return include_negative_ ? row + center_.row : row;
  }
  [[nodiscard]] auto map_col_to_internal(long long col) const -> long long {
    return include_negative_ ? col + center_.col : col;
  }

  bool include_negative_;
  unsigned long long width_;
  unsigned long long height_;
  Coordinates center_;
  std::vector<std::vector<T>> map;
};
} // namespace aoc2022
