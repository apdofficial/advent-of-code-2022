#include "day1.hpp"

#include <optional>
#include <span>
#include <vector>
#include <numeric>
#include <ranges>
#include <algorithm>
#include <execution>
#include <cassert>

template<typename Iter>
requires std::forward_iterator<Iter>
auto sum(Iter first, Iter last) {
    return std::accumulate(first, last, 0, [](auto acc, auto& item) {
        return acc + item.value_or(0);
    });
}

// T(n) = O(n*m)
auto aoc::day1::top_1_elf_calories(std::span<std::optional<int>> calories) -> std::optional<int> {
    int max_calories = 0;
    for (const auto &elf: calories | std::ranges::views::split(std::nullopt)) {
        max_calories = std::max(max_calories, sum(elf.begin(), elf.end()));
    }
    return max_calories;
}

// n = number of elves
// m = number of calories per elf
// T(n) = O(n*m + n * log(n))
auto aoc::day1::top_3_elf_calories(std::span<std::optional<int>> calories) -> std::optional<int> {
    assert(calories.size() >= 3 + 2); // at least 3 calorie entries for each elf and 2 std::nullopt elf separators
    std::vector<int> sums{};
    for(const auto elf: calories | std::views::split(std::nullopt)){
        sums.emplace_back(sum(elf.begin(), elf.end()));
    }
    auto n = sums.size();
    assert(n >= 3); // at least 3 elves are needed
    std::sort(std::execution::par_unseq, sums.begin(), sums.end(), std::less());
    return sums[n - 1] + sums[n - 2] + sums[n - 3];
}

// n = number of elves
// m = number of calories per elf
// T(n) = O(n*m)
auto aoc::day1::top_3_elf_calories_inplace(std::span<std::optional<int>> calories) -> std::optional<int> {
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