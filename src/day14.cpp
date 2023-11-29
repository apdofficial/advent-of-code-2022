#include "day14.hpp"

auto aoc::day14::parse_input(std::istream& stream, bool print) -> Scan {
    Scan scan{};
    Trace trace{};
    while (stream >> trace) {
        scan.append(std::move(trace));
    }
    if(print) {
        for(const auto& trc : scan.traces()) {
            std::cout << trc << '\n';
        }
    }
    return scan;
}

auto aoc::day14::part1(const Scan& scan) -> int {
    return 0;
}

auto aoc::day14::part2(const Scan& scan) -> int {
    return 0;
}
