#ifndef ADVENT_OF_CODE_2022_DAY4_HPP
#define ADVENT_OF_CODE_2022_DAY4_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>

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

    [[nodiscard]] bool is_sub_range_to(const Range& other) const {
        return (other.min <= min && min <= other.max) && (other.min <= max && max <= other.max);
    }

    [[nodiscard]] bool is_overlapping(const Range& other) const {
        return (other.min <= min && min <= other.max) || (other.min <= max && max <= other.max) ;
    }
};

void run_day_4();

#endif //ADVENT_OF_CODE_2022_DAY4_HPP
