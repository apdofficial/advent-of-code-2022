#include "day15.hpp"

#include <pstl/glue_execution_defs.h>

auto aoc::day15::load_input(std::istream& stream) -> Scan {
    Scan scan {};
    Sensor sensor{};
    while (stream >> sensor) {
        scan.add(std::move(sensor)
            );
    }
    return scan;
}

auto aoc::day15::part1(const Scan& scan, int row) -> int {
    return scan.get_coverage_at_row(row).size();
}

auto aoc::day15::part2(const Scan& scan_, bool print) -> int {
    auto scan = scan_;

    return -1;
}
