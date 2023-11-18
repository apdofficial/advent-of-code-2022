#pragma once

#include <unordered_set>

#include "util.h"

namespace aoc::day8 {
    using Forest = std::vector<std::vector<unsigned>>;

    struct Tree{
        unsigned i;
        unsigned j;
        unsigned scenic_score;

        bool operator>(const Tree& other) const {return scenic_score > other.scenic_score;}

        bool operator>=(const Tree& other) const {return scenic_score >= other.scenic_score;}

        bool operator<(const Tree& other) const {return scenic_score < other.scenic_score;}

        bool operator<=(const Tree& other) const {return scenic_score <= other.scenic_score;}

        friend std::ostream& operator<<(std::ostream &os, const Tree& tree){
            os << std::format("Tree(i={}, j={}, scenic_score={})\n", tree.j, tree.j, tree.scenic_score);
            return os;
        }

    };

    auto count_visible_trees(const Forest& forest) -> unsigned;

    auto calculate_scenic_score(const Forest &forest, const Tree& tree) -> unsigned;

    auto find_tree_with_highest_scenic_score(const Forest &forest) -> Tree;

}