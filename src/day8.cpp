#include "day8.hpp"

#include <ranges>
#include <algorithm>

// 3  0   3   7   3
// 2 [5] [5]  1   2
// 6 [5]  3  [3]  2
// 3  3  [5]  4   9
// 3  5   3   9   0

auto aoc::day8::count_visible_trees(const Forest &forest) -> unsigned {
    std::unordered_set<unsigned> visible_inner_trees{};
    // we assume a square matrix is given
    unsigned visible_outer_trees_num = forest.size() * 4 - 4; // top + bottom + lef + right - 4 duplicate corners
    // we assume a square matrix is given
    for (std::size_t i = 1; i < forest.size() - 1; ++i) {
        unsigned tallest_left = forest[i][0];
        for (std::size_t j = 1; j < forest.size() - 1; ++j) {
            if (forest[i][j] > tallest_left) {
                tallest_left = forest[i][j];
                visible_inner_trees.insert(forest.size() * i + j);
            }
        }
        unsigned tallest_right = forest[i][forest.size() - 1];
        for (int j = (int) forest.size() - 1; j > 0; --j) {
            if (forest[i][j] > tallest_right) {
                tallest_right = forest[i][j];
                visible_inner_trees.insert(forest.size() * i + j);
            }
        }
    }
    for (std::size_t j = 1; j < forest.size() - 1; ++j) {
        unsigned tallest_top = forest[0][j];
        for (unsigned i = 1; i < forest.size() - 1; ++i) {
            if (forest[i][j] > tallest_top) {
                tallest_top = forest[i][j];
                visible_inner_trees.insert(forest.size() * i + j);
            }
        }
        unsigned tallest_bottom = forest[forest.size() - 1][j];
        for (int i = (int) forest.size() - 1; i > 0; --i) {
            if (forest[i][j] > tallest_bottom) {
                tallest_bottom = forest[i][j];
                visible_inner_trees.insert(forest.size() * i + j);
            }
        }
    }
    return visible_inner_trees.size() + visible_outer_trees_num;
}

