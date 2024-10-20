#include "day15.hpp"

auto aoc2022::day15::load_input(std::istream& stream) -> Scan {
    Scan scan {};
    Sensor sensor{};
    while (stream >> sensor) {
        scan.add(std::move(sensor));
    }
    return scan;
}

auto aoc2022::day15::part1(const Scan& scan, long row) -> long {
    auto beacons = scan.get_beacons_at(row);
    auto coverage = scan.get_line_coverage_at(row);
    const auto n_beacons = std::ranges::count_if(beacons, [&coverage](const auto& beacon) {
        return coverage.contains(beacon);
    });
    return coverage.count_values() - n_beacons;
}

auto aoc2022::day15::part2(const Scan& scan, int limit) -> long {

    for(int row = limit; row > 0; --row) {
        auto coverage = scan.get_line_coverage_at(row);
        if ((row % 1000) == 0) {
            std::cout << "checking row " << row << "\n";
        }
        for(int col = 0; col < limit; ++col) {
            if (coverage.contains(col)) continue;
            return col * 4000000L + row;
        }
    }
    return 0;
}
