#include "day8.hpp"

// 3  0   3   7   3
// 2 [5] [5]  1   2
// 6 [5]  3  [3]  2
// 3  3  [5]  4   9
// 3  5   3   9   0

auto aoc::day8::count_visible_trees(const Forest &forest) -> unsigned {
    // we assume forest is a square matrix
    std::unordered_set<unsigned> visible_inner_trees{};
    auto update_visible_inner_trees = [&forest, &visible_inner_trees](const auto &i, const auto &j, auto &tallest) {
        if (forest[i][j] > tallest) {
            tallest = forest[i][j];
            visible_inner_trees.insert(forest.size() * i + j);
        }
    };
    for (unsigned i = 1; i < forest.size() - 1; ++i) {
        unsigned tallest_left = forest[i][0];
        for (std::size_t j = 1; j < forest.size() - 1; ++j) {
            update_visible_inner_trees(i, j, tallest_left); // left-to-right
        }
        unsigned tallest_right = forest[i][forest.size() - 1];
        for (int j = (int) forest.size() - 1; j > 0; --j) {
            update_visible_inner_trees(i, j, tallest_right); // right-to-left
        }
    }
    for (unsigned j = 1; j < forest.size() - 1; ++j) {
        unsigned tallest_top = forest[0][j];
        for (unsigned i = 1; i < forest.size() - 1; ++i) {
            update_visible_inner_trees(i, j, tallest_top); // top-down
        }
        unsigned tallest_bottom = forest[forest.size() - 1][j];
        for (int i = (int) forest.size() - 1; i > 0; --i) {
            update_visible_inner_trees(i, j, tallest_bottom); // bottom-to-top
        }
    }
    // inner + outer (top + bottom + lef + right - 4 duplicate corners)
    return visible_inner_trees.size() + forest.size() * 4 - 4;
}

auto aoc::day8::calculate_scenic_score(const Forest &forest, const Tree &tree) -> unsigned{
    return 0;
}

auto aoc::day8::find_highest_scenic_score(const Forest &forest) -> unsigned{
    return 0;
}
