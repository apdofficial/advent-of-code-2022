#include "day01.hpp"

// n = number of elves
// O(n)
auto aoc::day01::top_1_elf_calories(std::span<std::optional<int>> calories) -> std::optional<int> {
    int max1 = 0;
    auto op = [&max1](int accumulator, const std::optional<int> &line) {
        if (!line.has_value()) {
            if (accumulator > max1) max1 = accumulator;
            return 0;
        } else {
            return accumulator + line.value_or(0);
        }
    };
    auto accumulator = std::accumulate(calories.begin(), calories.end(), 0, op);
    // handle edge case when input does not end with empty string
    if (!calories.end()->has_value()) op(accumulator, std::nullopt);
    return max1;
}

// n = number of elves
// m = number of calories per elf
// O(n*m)
auto aoc::day01::top_3_elf_calories(std::span<std::optional<int>> calories) -> std::optional<int> {
    int max1 = 0, max2 = 0, max3 = 0;
    auto update_op = [&max1, &max2, &max3](int accumulator, const std::optional<int> &line) {
        if (!line.has_value()) {
            if (accumulator > max1) {
                if (max1 > max2) {
                    if (max2 > max3) max3 = max2;
                    max2 = max1;
                }
                max1 = accumulator;
            } else if (accumulator > max2) {
                if (max2 > max3) max3 = max2;
                max2 = accumulator;
            } else if (accumulator > max3) {
                max3 = accumulator;
            }
            return 0;
        } else {
            return accumulator + line.value_or(0);
        }
    };
    auto accumulator = std::accumulate(calories.begin(), calories.end(), 0, update_op);
    // handle edge case when input does not end with empty string
    if (!calories.end()->has_value()) update_op(accumulator, std::nullopt);
    return max1 + max2 + max3;
}