#pragma once


#include <common.hpp>

#include "util.h"
#include <iostream>
#include <ranges>

namespace aoc::day14 {
    static auto file_path = get_day_file_path(14);

    using Path = std::vector<Coordinates>;

    struct Trace {
        Trace() = default;

        friend auto operator>>(std::istream& is, Trace& trace) -> std::istream& {
            int row_prev = -1, col_prev = -1;
            int row = 0, col = 0;
            char delimiter;
            std::string coord_str, line;
            getline(is, line, '\n');
            std::istringstream iss(line);
            Path turning_coordinates{};
            while (iss >> col >> delimiter >> row) {
                if (row == row_prev) {
                    for (int col_: std::views::iota(std::min(col_prev, col), std::max(col_prev, col) + 1)) {
                        trace.path_.emplace_back(col_, row);
                    }
                }
                if (col == col_prev) {
                    for (int row_: std::views::iota(std::min(row_prev, row), std::max(row_prev, row) + 1)) {
                        trace.path_.emplace_back(col, row_);
                    }
                }
                row_prev = row;
                col_prev = col;
                iss >> delimiter >> delimiter;
            }
            return is;
        }

        friend auto operator<<(std::ostream& os, const Trace& trace) -> std::ostream& {
            for (const auto& [x, y]: trace.path_) {
                os << x << ", " << y << " -> ";
            }
            return os;
        }

        [[nodiscard]] auto path() const { return path_; }

    private:
        Path path_;
    };

    using Traces = std::vector<Trace>;
    using Scanmap_Row = std::vector<char>;
    using SandMap = std::vector<Scanmap_Row>;

    struct Scan {
        Scan() {
            set_start(default_start);
        }

        void append(Trace&& trace) {
            for (auto& coord: trace.path()) {
                map_[coord] = CHAR_ROCK;
                rocks_bounding_.update(coord);
            }
            rock_traces_.emplace_back(std::move(trace));
        }

        [[nodiscard]] auto rock_traces() const { return rock_traces_; }

        friend auto operator<<(std::ostream& os, Scan& scan) -> std::ostream& {
            const auto rows = std::views::iota(scan.sand_bounding_.min_row, scan.sand_bounding_.max_row + 1);
            const auto cols = std::views::iota(scan.sand_bounding_.min_col, scan.sand_bounding_.max_col + 1);
            for (const auto& row: rows) {
                for (const auto& col: cols) {
                    os << scan.map_.at(row,col);
                }
                os << '\n';
            }
            return os;
        }

        void set_start(const Coordinates& start) {
            rocks_bounding_.update(default_start);
            map_[start] = CHAR_START;
        }

        void set_floor(int row) {
            for (unsigned col: map_.iota_cols()) {
                map_.at(row,col) = CHAR_ROCK;
            }
            rocks_bounding_.max_row = std::max(rocks_bounding_.max_row, row);
        }

        static constexpr Coordinates default_start{500, 0};

        [[nodiscard]] auto bounding() const { return rocks_bounding_; }
        [[nodiscard]] auto map() -> auto& { return map_; }

        static constexpr char CHAR_SAND = 'o';
        static constexpr char CHAR_ROCK = '#';
        static constexpr char CHAR_AIR = '.';
    private:
        static constexpr char CHAR_START = '+';
        Map<char> map_{1'000, 1'000, CHAR_AIR};
        Traces rock_traces_{};
        BoundingBox rocks_bounding_{1'000, -1, 1'000, -1};
        BoundingBox sand_bounding_{1'000, -1, 1'000, -1};
    };

    [[nodiscard]] auto parse_input(std::istream& stream, bool print = false) -> Scan;

    [[nodiscard]] auto part1(const Scan& scan, bool print = false) -> int;

    [[nodiscard]] auto part2(const Scan& scan, bool print = false) -> int;
}
