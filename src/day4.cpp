#include <iomanip>
#include "day4.hpp"

std::string const DAY_NR = "4";

// Asymptotic analysis
// complexity is linear O(n)
// no redundant computation
int num_of_fully_contained_ranges(const std::vector<std::pair<Range, Range>>& lines){
    auto accumulateOp = [](auto accumulator, auto& line){ // n
        if (line.first.is_sub_range_to(line.second) || line.second.is_sub_range_to(line.first))
            return accumulator + 1;
        return accumulator;
    };
    return std::accumulate(lines.begin(), lines.end(),0, accumulateOp);
}

// Asymptotic analysis
// complexity is linear O(n)
// no redundant computation
int num_of_overlapping_ranges(const std::vector<std::pair<Range, Range>>& lines){
    auto accumulateOp = [](auto accumulator, auto& line){ // n
        if (line.first.is_overlapping(line.second) || line.second.is_overlapping(line.first))
            return accumulator + 1;
        return accumulator;
    };
    return std::accumulate(lines.begin(), lines.end(),0, accumulateOp);
}


void run_day_4(){
    std::string const fileName = "day" + DAY_NR + ".txt";
    std::cout << "--Day " << DAY_NR << " START--" << std::endl;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(fileName) << "\n";
        return;
    }

    std::vector<std::pair<Range,Range>> lines;
    char delimiter;
    uint32_t lMin, lMax, rMin, rMax;
    while (file >> lMin >> delimiter >> lMax >> delimiter >> rMin >> delimiter >> rMax ) {
        lines.emplace_back(Range {.min = lMin, .max = lMax},Range {.min = rMin, .max = rMax});
    }

    std::cout << "num_of_fully_contained_ranges:  " << num_of_fully_contained_ranges(lines) << std::endl;
    std::cout << "num_of_overlapping_ranges:      " << num_of_overlapping_ranges(lines) << std::endl;

    std::cout << "--Day " << DAY_NR << " END--\n" << std::endl;
    return;
}