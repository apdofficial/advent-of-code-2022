#pragma once


#include "util.h"
#include <iostream>
#include <ranges>

namespace aoc::day14 {
    static auto file_path = get_day_file_path(14);

    struct Coordinates {
        int col = 0;
        int row = 0;

        bool operator!=(const Coordinates& rhs) const { return col != rhs.col || row != rhs.row; }
    };

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

    struct BoundingBox {
        int min_row = 0;
        int max_row = 0;
        int min_col = 0;
        int max_col = 0;
    };

    struct Scan {
        Scan() {
            set_start(default_start);
        }

        void append(Trace&& trace) {
            for (auto& coord: trace.path()) {
                map_[coord.row][coord.col] = rock_char;
                update_bounding_box(coord);
            }
            rock_traces_.emplace_back(std::move(trace));
        }

        [[nodiscard]] auto rock_traces() const { return rock_traces_; }

        [[nodiscard]] auto operator[](const unsigned row) -> Scanmap_Row& { return map_[row]; }

        [[nodiscard]] auto operator[](const Coordinates& coord) -> auto& { return map_[coord.row][coord.col]; }

        void update_bounding_box(const Coordinates& coord) {
            bounding_.min_row = std::min(bounding_.min_row, coord.row);
            bounding_.max_row = std::max(bounding_.max_row, coord.row);
            bounding_.min_col = std::min(bounding_.min_col, coord.col);
            bounding_.max_col = std::max(bounding_.max_col, coord.col);
        }

        void update_bounding_box_automatically() {
            sand_bounding_ = bounding_;
            for (auto & row : map_) {
                for (int col = 0; col < row.size(); ++col) {
                    if (row[col] == sand_char) {
                        if (col < sand_bounding_.min_col) sand_bounding_.min_col = col;
                        if (col > sand_bounding_.max_col) sand_bounding_.max_col = col;
                    }
                }
            }
        }

        friend auto operator<<(std::ostream& os, Scan& scan) -> std::ostream& {
            scan.update_bounding_box_automatically();
            const auto rows = std::views::iota(scan.sand_bounding_.min_row, scan.sand_bounding_.max_row + 1);
            const auto cols = std::views::iota(scan.sand_bounding_.min_col, scan.sand_bounding_.max_col + 1);
            for (const auto& row: rows) {
                for (const auto& col: cols) {
                    os << scan.map_[row][col];
                }
                os << '\n';
            }
            return os;
        }

        void set_start(const Coordinates& start) {
            update_bounding_box(default_start);
            map_[start.row][start.col] = start_char;
        }

        void set_floor(int row) {
            for (int col: std::views::iota(0, 1'000)) {
                map_[row][col] = rock_char;
            }
            bounding_.max_row = std::max(bounding_.max_row, row);
        }

        static constexpr Coordinates default_start{500, 0};

        [[nodiscard]] auto bounding() const { return bounding_; }

        static constexpr char sand_char = 'o';
        static constexpr char rock_char = '#';
        static constexpr char air_char = '.';

    private:
        static constexpr char start_char = '+';
        SandMap map_ = std::vector(1'000, std::vector(1'000, air_char));
        Traces rock_traces_{};
        BoundingBox bounding_{1'000, -1, 1'000, -1};
        BoundingBox sand_bounding_{1'000, -1, 1'000, -1};
    };

    [[nodiscard]] auto parse_input(std::istream& stream, bool print = false) -> Scan;

    [[nodiscard]] auto part1(const Scan& scan, bool print = false) -> int;

    [[nodiscard]] auto part2(const Scan& scan, bool print = false) -> int;
}
