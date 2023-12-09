#pragma once

#include "util.h"
#include "common.hpp"
#include <iostream>
#include <fmt/core.h>
#include <ranges>
#include <regex>
#include <set>
#include <string>

namespace aoc::day15 {
    static auto file_path = get_day_file_path(15);

    struct Sensor: Coordinates {
        Coordinates beacon;
        long distance;

        friend auto operator>>(std::istream& is, Sensor& sensor) -> std::istream& {
            std::string line;
            getline(is, line, '\n');
            if (line.empty()) {
                while (getline(is, line, '\n')) {
                    if (!line.empty()) break;
                }
            }
            if (line.empty()) return is;
            std::istringstream iss(line);
            const std::regex pattern(R"(Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))");
            std::smatch match;
            if (std::regex_search(line, match, pattern)) {
                sensor.col = std::stoi(match[1].str());
                sensor.row = std::stoi(match[2].str());
                sensor.beacon.col = std::stoi(match[3].str());
                sensor.beacon.row = std::stoi(match[4].str());
            }
            sensor.distance = std::abs(sensor.beacon.row - sensor.row) + std::abs(sensor.beacon.col - sensor.col);
            return is;
        }

        friend auto operator<<(std::ostream& os, const Sensor& snsr) -> std::ostream& {
            os << std::format("Sensor at x={}, y={}: closest beacon is at x={}, y={}", snsr.col, snsr.row,
                              snsr.beacon.col, snsr.beacon.row);
            return os;
        }

        [[nodiscard]] auto row_coverage(const long row_candidate) const -> std::optional<Range> {
            const auto row_distance = distance - std::abs(row_candidate - row);
            if (row_distance < 0) return std::nullopt;
            return Range{.start = col - row_distance, .end = col + row_distance + 1};
        }
    };

    using Sensors = std::vector<Sensor>;

    struct Scan {
        void add(Sensor&& sensor) { sensors_.emplace_back(std::move(sensor)); }

        [[nodiscard]] auto get_beacons_at(long row) const -> std::set<long> {
            std::set<long> beacons{};
            for (const auto& sensor: sensors_) {
                if (sensor.beacon.row == row) {
                    beacons.insert(sensor.beacon.col);
                }
            }
            return beacons;
        }

        [[nodiscard]] auto get_line_coverage_at(const long row) const -> RangeSet {
            RangeSet set{};
            for (const auto& sensor: sensors_) {
                if (const auto coverage = sensor.row_coverage(row)) {
                    set.insert(coverage.value());
                }
            }
            return set;
        }

        [[nodiscard]] auto sensors() const { return sensors_; }

    private:
        Sensors sensors_{};
    };

    auto load_input(std::istream& stream) -> Scan;

    [[nodiscard]] auto part1(const Scan& scan, long row) -> long;

    [[nodiscard]] auto part2(const Scan& scan, int limit) -> long;
}
