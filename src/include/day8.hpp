#pragma once

#include <unordered_set>

#include "util.h"

namespace aoc::day8 {
    using Forest = std::vector<std::vector<unsigned>>;
    using Tree = std::pair<unsigned, unsigned>;

    auto count_visible_trees(const Forest& forest) -> unsigned;

    auto calculate_scenic_score(const Forest &forest, const Tree &tree) -> unsigned;

    auto find_highest_scenic_score(const Forest &forest) -> unsigned;

}