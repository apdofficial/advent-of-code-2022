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

auto aoc::day8::calculate_scenic_score(const Forest &forest, const Tree& tree) -> unsigned {
    if(tree.i == 0 || tree.i == forest.size()-1) return 0;
    if(tree.j == 0 || tree.j == forest.size()-1) return 0;
    auto tree_height = forest[tree.i][tree.j];
    unsigned score_r = 0;
    for (unsigned  j = tree.j + 1; j < forest.size(); ++j){ // scan-to-right
        ++score_r;
        if(forest[tree.i][j] >= tree_height) break;
    }
    unsigned score_l = 0;
    for (int  j = (int)tree.j - 1; j >= 0; --j){ // scan-to-left
        ++score_l;
        if(forest[tree.i][j] >= tree_height) break;
    }
    unsigned score_d = 0;
    for (unsigned  i = tree.i + 1; i < forest.size(); ++i){ // scan-to-down
        ++score_d;
        if(forest[i][tree.j] >= tree_height) break;
    }
    unsigned score_t = 0;
    for (int i = (int)tree.i-1; i >= 0; --i){ // scan-to-up
        ++score_t;
        if(forest[i][tree.j] >= tree_height) break;
    }
    score_r = (score_r > 0 ? score_r : 1);
    score_l = (score_l > 0 ? score_l : 1);
    score_d = (score_d > 0 ? score_d : 1);
    score_t = (score_t > 0 ? score_t : 1);
    return score_r * score_l * score_d * score_t;
}

auto aoc::day8::find_tree_with_highest_scenic_score(const Forest &forest) -> Tree {
    Tree scenic_tree {0, 0, 0};
    for (unsigned  i = 0; i < forest.size(); ++i){
        for (unsigned  j = 0; j < forest.size(); ++j){
            Tree tree {i, j, 0};
            tree.scenic_score = calculate_scenic_score(forest, tree);
            if(tree > scenic_tree) scenic_tree = tree;
        }
    }
    return scenic_tree;
}
