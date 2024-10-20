#include "day03.hpp"

// n = number of elves
// m = number of items for each elf
// T(n, m) = n * (m/2 * (m/2 + m/2)) => O(n * (m^2)/2)
auto aoc2022::day03::sum_item_priorities_of_both_compartments(std::span<const std::string> lines) -> int{
    auto accumulateOp = [](auto accumulator, auto& line){ // n
        int lineSum = 0;
        std::vector<char> registered;
        std::string firstHalf = line.substr(0, line.length()/2);
        std::string secondHalf = line.substr(line.length()/2);
        for (char const &c: firstHalf){ // m/2
            if (secondHalf.find(c) != std::string::npos && // O(m/2)
                std::find(registered.begin(), registered.end(), c) == registered.end()){ // O(m/2)
                lineSum += isupper(c) ? c - 'A' + 27 : c - 'a' + 1;
                registered.push_back(c);
            }
        }
        return accumulator + lineSum;
    };
    return std::accumulate(lines.begin(), lines.end(), 0, accumulateOp);
}

// n = number of elves
// m = number of items for each elf
// T(n, m) = n * (m * (m + m + m)) => O(n * m^2)
auto aoc2022::day03::sum_grouped_item_priorities_of_both_compartments(std::span<const std::string> lines) -> int{
    int groupSum = 0, groupIndex = 1;
    std::vector<std::string> group;
    std::vector<char> registered;
    auto accumulateOp = [&groupSum, &groupIndex, &group, &registered](auto accumulator, auto& line){ // n
        if (groupIndex == 4){ groupIndex = 1; groupSum = 0; group.clear(); registered.clear();}
        if (groupIndex == 3) {
            for (char const &c: line) { // m
                if (group[0].find(c) != std::string::npos && group[1].find(c) != std::string::npos && // m + m
                    std::find(registered.begin(), registered.end(), c) == registered.end()) { // m
                    groupSum += isupper(c) ? c - 'A' + 27 : c - 'a' + 1;
                    registered.push_back(c);
                }
            }
        }
        if (groupIndex == 1 || groupIndex == 2) group.push_back(line);
        groupIndex++;
        return accumulator + groupSum;
    };
    return std::accumulate(lines.begin(), lines.end(), 0, accumulateOp);
}
