#pragma once

#include <vector>
#include <string>
#include <ranges>

namespace aoc {
    using InputLines = std::vector<std::string>;

    struct Range {
        long start;
        long end;
    };

    struct Coordinates {
        int row = 0;
        int col = 0;
        bool operator!=(const Coordinates& rhs) const { return col != rhs.col || row != rhs.row; }
        bool operator==(const Coordinates& rhs) const { return col == rhs.col && row == rhs.row; }

        friend auto operator+(const Coordinates& lhs, const Coordinates& rhs) -> Coordinates {
            return {.row = lhs.row + rhs.row, .col = lhs.col + rhs.col,};
        }
    };

    struct BoundingBox {
        int min_row = 0;
        int max_row = 0;
        int min_col = 0;
        int max_col = 0;

        void update(const Coordinates& coord) {
            min_row = std::min(min_row, coord.row);
            max_row = std::max(max_row, coord.row);
            min_col = std::min(min_col, coord.col);
            max_col = std::max(max_col, coord.col);
        }
    };

    template<typename T>
    struct Map {
        explicit Map(unsigned long long width, unsigned long long height, T init, bool include_negative = false):
            include_negative_(include_negative),
            width_(width * (include_negative ? 2 : 1)),
            height_(height * (include_negative ? 2 : 1)),
            center_(include_negative ? height : 0, include_negative ? width : 0),
            map(height_, std::vector(width_, init)) {

        }

        [[nodiscard]] auto at(long long row, long long col) const -> auto& {
            return map[map_row_to_internal(row)][map_col_to_internal(col)];
        }

        [[nodiscard]] auto at(long long row, long long col) -> auto& {
            return map[map_row_to_internal(row)][map_col_to_internal(col)];
        }

        [[nodiscard]] auto operator[](const Coordinates& crd) const -> auto& {
            return map[map_row_to_internal(crd.row)][map_col_to_internal(crd.col)];
        }

        [[nodiscard]] auto operator[](const Coordinates& crd) -> auto& {
            return map[map_row_to_internal(crd.row)][map_col_to_internal(crd.col)];
        }

        [[nodiscard]] auto begin() const { return map.begin(); }
        [[nodiscard]] auto end() const { return map.end(); }

        [[nodiscard]] auto iota_rows() const {
            auto split = height_/2;
            return std::views::iota(include_negative_ ? -split : 0, include_negative_ ? split : height_);
        }
        [[nodiscard]] auto iota_cols() const {
            auto split = width_/2;
            return std::views::iota(include_negative_ ? -split : 0, include_negative_ ? split : width_);
        }

    private:
        [[nodiscard]] auto rows() const { return map.size(); }
        [[nodiscard]] auto cols() const { return map[0].size(); }

        [[nodiscard]] auto map_row_to_internal(long long row) const -> long long {
            return include_negative_ ? row + center_.row : row;
        }
        [[nodiscard]] auto map_col_to_internal(long long col) const -> long long {
            return include_negative_ ? col + center_.col : col;
        }

        bool include_negative_;
        Coordinates center_;
        unsigned long long width_;
        unsigned long long height_;
        std::vector<std::vector<T>> map;
    };
}
