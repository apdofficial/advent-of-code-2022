#pragma once

#include "util.h"
#include <iostream>
#include <fmt/core.h>
#include <ranges>
#include <iostream>
#include <regex>
#include <string>

namespace aoc::day15 {
    static auto file_path = get_day_file_path(15);

    struct Coordinates {
        int col = 0;
        int row = 0;
        bool operator!=(const Coordinates& rhs) const { return col != rhs.col || row != rhs.row; }
        bool operator==(const Coordinates& rhs) const { return col == rhs.col && row == rhs.row; }
    };

    struct Sensor: Coordinates {
        Coordinates closest_beacon;

        friend auto operator>>(std::istream& is, Sensor& sensor) -> std::istream& {
            std::string line;
            getline(is, line, '\n');
            if (line.empty()) {
                while (getline(is, line, '\n')) {
                    if(!line.empty()) break;
                }
            }
            if (line.empty()) return is;
            std::istringstream iss(line);
            const std::regex pattern(R"(Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))");
            std::smatch match;
            if (std::regex_search(line, match, pattern)) {
                const auto col1 =  std::stoi(match[1].str()); sensor.col = col1;
                const auto row1 =  std::stoi(match[2].str()); sensor.row = row1;
                const auto col2 =  std::stoi(match[3].str()); sensor.closest_beacon.col = col2;
                const auto row2 =  std::stoi(match[4].str()); sensor.closest_beacon.row = row2;
            }
            return is;
        }

        friend auto operator<<(std::ostream& os, const Sensor& snsr) -> std::ostream&  {
            os << std::format("Sensor at x={}, y={}: closest beacon is at x={}, y={}", snsr.col, snsr.row, snsr.closest_beacon.col, snsr.closest_beacon.row);
            return os;
        }
    };

    using Sensors = std::vector<Sensor>;

    template<typename T>
    struct ScanMap {
        explicit ScanMap(unsigned width, unsigned height, T init):
        width_(width),
        height_(height),
        map{height_, std::vector(width_, init)} {}

        auto operator[](unsigned row)  -> auto& { return map[row];}
        auto operator[](unsigned row) const -> auto { return map[row];}

        auto operator[](const Coordinates crd)  -> auto& { return map[crd.row][crd.col];}
        auto operator[](const Coordinates crd) const -> auto { return map[crd.row][crd.col];}

        [[nodiscard]] auto width() const { return width_; }
        [[nodiscard]] auto height() const { return height_; }

    private:
        unsigned width_ = 0;
        unsigned height_ = 0;
        std::vector<std::vector<T>> map;
    };

    struct Scan {

        void append(Sensor &&sensor) {
            map_[sensor] = sensor_char;
            map_[sensor.closest_beacon] = beacon_char;
            sensors_.emplace_back(std::move(sensor));
        }

        friend auto operator<<(std::ostream& os, const Scan& scan) -> std::ostream&  {
            for(unsigned row: std::views::iota(0u, scan.map_.height())) {
                for(unsigned col: std::views::iota(0u, scan.map_.width())) {
                    os << scan.map_[row][col];
                }
                os << '\n';
            }
            return os;
        }

        static constexpr char sensor_char = 'S';
        static constexpr char beacon_char = 'B';
    private:
        Sensors sensors_{};
        ScanMap<char> map_{26, 23,'.'};
    };


    [[nodiscard]] auto parse_input(std::istream& stream, bool print = false) -> Scan;

    [[nodiscard]] auto part1(const Scan& scan, bool print = false) -> int;

    [[nodiscard]] auto part2(const Scan& scan, bool print = false) -> int;
}
