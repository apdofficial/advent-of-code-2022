#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <span>

namespace aoc::day04 {

    // (ref)    --|---|---
    // (case 1) |--|------ left overlap
    // (case 2) -----|---| right overlap
    // (case 3) --|---|--- exactly the same
    // (case 4) --|--|---- sub range
    // (case 5) ---|--|--- sub range
    // (case 6) ---|-|---- sub range
    struct Range {
        uint32_t min;
        uint32_t max;

        [[nodiscard]] bool is_sub_range_to(const Range &other) const {
            return (other.min <= min && min <= other.max) && (other.min <= max && max <= other.max);
        }

        [[nodiscard]] bool is_overlapping(const Range &other) const {
            return (other.min <= min && min <= other.max) || (other.min <= max && max <= other.max);
        }

        friend std::istream& operator>>(std::istream & is, Range& other) {
            char delimiter {};
            is >> other.min >> delimiter >> other.max;
            return is;
        }
    };

    auto map_to_ranges(std::span<const  std::string> lines) -> std::vector<std::pair<Range, Range>>;

    auto num_of_fully_contained_ranges(std::span<const std::pair<Range, Range>> lines) -> int;

    auto num_of_overlapping_ranges(std::span<const std::pair<Range, Range>> lines) -> int;
}