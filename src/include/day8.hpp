#pragma once

#include <unordered_set>

#include "util.h"

namespace aoc::day8 {
    using Forest = std::vector<std::vector<unsigned>>;

    auto count_visible_trees(const Forest& forest) -> unsigned;
}