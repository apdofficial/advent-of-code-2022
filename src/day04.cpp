#include "day04.hpp"

auto aoc::day04::map_to_ranges(std::span<const std::string> lines) -> std::vector<std::pair<Range, Range>>{
    std::vector<std::pair<Range,Range>> ranges;
    char delimiter;
    Range left{};
    Range right{};
    for (const auto& line: lines) {
        std::istringstream lineStream{line};
        lineStream >> left >> delimiter >> right;
        ranges.emplace_back(left,right);
    }
    return ranges;
}


// O(n)
auto aoc::day04::num_of_fully_contained_ranges(std::span<const std::pair<Range, Range>> lines) -> int{
    auto accumulateOp = [](auto accumulator, auto& line){ // n
        if (line.first.is_sub_range_to(line.second) || line.second.is_sub_range_to(line.first))
            return accumulator + 1;
        return accumulator;
    };
    return std::accumulate(lines.begin(), lines.end(),0, accumulateOp);
}

// O(n)
auto aoc::day04::num_of_overlapping_ranges(std::span<const std::pair<Range, Range>> lines) -> int{
    auto accumulateOp = [](auto accumulator, auto& line){ // n
        if (line.first.is_overlapping(line.second) || line.second.is_overlapping(line.first))
            return accumulator + 1;
        return accumulator;
    };
    return std::accumulate(lines.begin(), lines.end(),0, accumulateOp);
}