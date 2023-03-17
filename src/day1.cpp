#include "day1.hpp"
#include "aoc.hpp"

#include <optional>
#include <span>
#include <vector>
#include <numeric>
#include <ranges>


auto compute_calorie_sums(std::span<std::optional<int>> calories) -> std::vector<int>{
    auto elf_groups = calories | std::ranges::views::split(std::nullopt);
    std::vector<int> sums;
    // n * m
    for (const auto &elf: elf_groups) { // n
        int accumulator = 0;
        for (auto calorie: elf) { //m
            accumulator = accumulator + calorie.value_or(0);
        }
        sums.push_back(accumulator);
    }
    return sums;
}

// T(n) = O(n)
auto aoc::day1::top_1_elf_calories(std::span<std::optional<int>> calories) -> std::optional<int>
{
    auto elf_groups = calories | std::ranges::views::split(std::nullopt);
    int max_calories = 0;
    for (const auto &elf: elf_groups) {
        int accumulator = 0;
        // rv::split is not allowing to use ast algorithms e.g., std::accumulator
        for (auto calorie: elf) {
            accumulator = accumulator + calorie.value_or(0);
        }
        max_calories = std::max(max_calories, accumulator);
    }
    return max_calories;
}


// n = number of elves
// m = number of calories per elf
// T(n) = O(n*m + n^2)
auto aoc::day1::top_3_elf_calories_bubble(std::span<std::optional<int>> calories) -> std::optional<int>
{
    assert(calories.size() >= 3 + 2); // at least 3 calorie entries for each elf and 2 std::nullopt elf separators
    std::vector<int> sums = compute_calorie_sums(calories);
    auto n = sums.size();
    assert(n >= 3); // at least 3 elves are needed
    aoc::bubble_sort(sums);
    return sums[n-1] + sums[n-2] + sums[n-3];
}


// n = number of elves
// m = number of calories per elf
// T(n) = O(n*m + n^2) however expected average running time is theta(n log(n)).
auto aoc::day1::top_3_elf_calories_quick(std::span<std::optional<int>> calories) -> std::optional<int>
{
    assert(calories.size() >= 3 + 2); // at least 3 calorie entries for each elf and 2 std::nullopt elf separators
    std::vector<int> sums = compute_calorie_sums(calories);
    auto n = sums.size();
    assert(n >= 3); // at least 3 elves are needed
    aoc::quick_sort(sums, 0, n-1);
    return sums[n-1] + sums[n-2] + sums[n-3];
}


// n = number of elves
// m = number of calories per elf
// T(n) = O(n*m)
auto aoc::day1::top_3_elf_calories_inplace(std::span<std::optional<int>> calories) -> std::optional<int>
{
    int max1 = 0, max2 = 0, max3 = 0;
    auto update_op = [&max1, &max2, &max3](int accumulator, const std::optional<int> &line){
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