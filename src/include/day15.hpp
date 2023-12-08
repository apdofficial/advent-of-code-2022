#pragma once

#include "util.h"
#include "common.hpp"
#include <iostream>
#include <fmt/core.h>
#include <ranges>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <bits/ranges_algo.h>

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
            os << std::format("Sensor at x={}, y={}: closest beacon is at x={}, y={}",
                snsr.col, snsr.row, snsr.beacon.col, snsr.beacon.row);
            return os;
        }

        [[nodiscard]] auto row_coverage(const int row_candidate) const -> std::optional<Range> {
            const auto row_distance = distance - std::abs(row_candidate - row);
            if (row_distance < 0) return std::nullopt;
            return Range{.start = col - row_distance, .end = col + row_distance};
        }
    };

    using Sensors = std::vector<Sensor>;

    struct Scan {

        void add(Sensor&& sensor) { sensors_.emplace_back(std::move(sensor)); }

        [[nodiscard]] auto get_beacons_at(int row) const -> std::vector<Coordinates> {
            std::vector<Coordinates> beacons{};
            for (const auto& sensor: sensors_) {
                if (sensor.beacon.row == row) {
                    const auto exist = std::ranges::find_if(beacons, [&sensor](const auto& beacon) {
                        return beacon.row == sensor.beacon.row && beacon.col == sensor.beacon.col;
                    }) != beacons.end();
                    if (!exist) {beacons.emplace_back(sensor.beacon);}
                }
            }
            return beacons;
        }

        [[nodiscard]] auto get_coverage_at_row(int row) const -> std::set<long> {
            auto beacons = get_beacons_at(row);
            const auto sensors = sensors_;
            std::set<long> row_coverage{};
            for (const auto& sensor: sensors) {
                if (const auto coverage = sensor.row_coverage(row)) {
                    for(auto sensor_col: std::ranges::iota_view(coverage->start, coverage->end + 1)) {
                        const auto is_not_beacon = std::ranges::find_if(beacons, [sensor_col](const auto& b) {
                            return b.col == sensor_col;
                        }) == beacons.end();
                        if (is_not_beacon) {
                            row_coverage.insert(sensor_col);
                        }
                    }
                }
            }
            return row_coverage;
        }

        [[nodiscard]] auto sensors() const { return sensors_; }

    private:
        Sensors sensors_{};
    };


    auto load_input(std::istream& stream) -> Scan;

    [[nodiscard]] auto part1(const Scan& scan, int row) -> int;

    [[nodiscard]] auto part2(const Scan& scan, bool print = false) -> int;
}
