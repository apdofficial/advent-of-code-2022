#include "day15.hpp"

auto aoc::day15::parse_input(std::istream& stream, bool print) -> Scan {
    Scan scan{};
    Sensor sensor{};
    while (stream >> sensor) {
        std::cout << sensor << '\n';
        if(print) scan.append(std::move(sensor));
    }
    if(print) std::cout << scan << '\n';
    return scan;
}

auto aoc::day15::part1(const Scan& scan_, bool print) -> int {
    auto scan = scan_;

    return -1;
}

auto aoc::day15::part2(const Scan& scan_, bool print) -> int {
    auto scan = scan_;

    return -1;
}
