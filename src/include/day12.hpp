#pragma once

#include <ranges>
#include <algorithm>
#include <queue>
#include <valarray>
#include <queue>
#include <thread>
#include <fmt/core.h>
#include <cassert>
#include <fmt/color.h>
#include <execution>

#include "util.h"

namespace aoc2022::day12 {
    struct Point {
        explicit Point(int x, int y): x_(x), y_(y) {}

        [[nodiscard]] auto x() const -> auto { return x_; }

        [[nodiscard]] auto y() const -> auto { return y_; }

        bool operator==(const Point &other) const {
            return x_ == other.x_ && y_ == other.y_;
        }

        bool operator!=(const Point &other) const {
            return x_ != other.x() || y_ != other.y();
        }

    protected:
        int x_ = 0;
        int y_ = 0;
    };

    struct ElevationPoint: public Point {

        explicit ElevationPoint(char c, int x, int y): Point(x, y) {
            if (c == 'S') {
                height_ = -1;
            } else if (c == 'E') {
                height_ = -2;
            } else {
                if (c < 'A' || c > 'z') throw std::runtime_error("Invalid elevation character");
                if (c <= 'Z') {
                    height_ = c - 'A';
                } else {
                    height_ = c - 'a';
                }
            }
        }

        [[nodiscard]] auto is_start() const -> bool { return height_ == -1; }

        [[nodiscard]] auto is_end() const -> bool { return height_ == -2; }

        [[nodiscard]] auto height() const -> int { return height_; }

        [[nodiscard]] auto neighbours(const std::vector<std::vector<ElevationPoint>> &map) const -> auto {
            std::vector<ElevationPoint> neighbours{};
            if (x_ > 0) neighbours.emplace_back(map[x_ - 1][y_]);
            if (x_ < map.size() - 1) neighbours.emplace_back(map[x_ + 1][y_]);
            if (y_ > 0) neighbours.emplace_back(map[x_][y_ - 1]);
            if (y_ < map[x_].size() - 1) neighbours.emplace_back(map[x_][y_ + 1]);
            return neighbours;
        }

        friend auto operator<<(std::ostream &os, const ElevationPoint &point) -> std::ostream & {
            if (point.is_start()) {
                os << "S";
            } else if (point.is_end()) {
                os << "E";
            } else {
                os << "(" << point.x() << "," << point.y() << ")";
            }
            return os;
        }

    private:
        int height_ = 0;
    };

    using ElevationMap = std::vector<std::vector<ElevationPoint>>;
    using ElevationPath = std::vector<ElevationPoint>;

    template<typename T>
    struct ElevationMatrix {
        using Container = std::vector<std::vector<T>>;
        using val_t = T;
        using const_val_t = const T;
        using ref_t = T &;
        using const_ref_t = const T &;

        explicit ElevationMatrix(std::size_t rows, std::size_t cols, T init): container_(rows,
                                                                                         std::vector<T>(cols, init)) {}

        auto operator[](const Point &point) -> ref_t { return container_[point.x()][point.y()]; }

        auto operator[](const Point &point) const -> const_ref_t { return container_[point.x()][point.y()]; }

        auto operator[](const ElevationPoint &point) -> ref_t { return container_[point.x()][point.y()]; }

        auto operator[](const ElevationPoint &point) const -> const_ref_t { return container_[point.x()][point.y()]; }

        auto operator[](const std::optional<ElevationPoint> &point) -> std::optional<val_t> & {
            if (!point.has_value()) return std::nullopt;
            return container_[point.value().x()][point.value().y()];
        }

        auto operator[](const std::optional<ElevationPoint> &point) const -> const std::optional<val_t> & {
            if (!point.has_value()) return std::nullopt;
            return container_[point.value().x()][point.value().y()];
        }

        auto operator[](std::size_t row) -> std::vector<T> & { return container_[row]; }

        auto operator[](std::size_t row) const -> const std::vector<T> & { return container_[row]; }

    private:
        Container container_;
    };

    using Distance = long long int;
    enum class Visited {
        TRUE, FALSE
    };

    [[nodiscard]] auto parse_input(const std::vector<std::string> &data) -> ElevationMap;

    /**
     * Find the shortest path from start to end using Dijkstra's algorithm
     * @param map
     * @param start
     * @param end
     * @param visualise
     * @return
     */
    [[nodiscard]] auto
    find_shortest_path(ElevationMap &map, const ElevationPoint &start, const ElevationPoint &end,
                       bool visualise = false) -> ElevationPath;

    /**
     * Find the shortest path from the lowest height to end using Dijkstra's algorithm
     * @param map
     * @param end
     * @param visualise
     * @return
     */
    [[nodiscard]] auto find_shortest_path_from_first_lowest(ElevationMap &map, const ElevationPoint &end,
                                                            bool visualise = false) -> ElevationPath;

    [[nodiscard]] auto find_start(const ElevationMap &map) -> std::optional<ElevationPoint>;

    [[nodiscard]] auto find_end(const ElevationMap &map) -> std::optional<ElevationPoint>;

    void print_map(const ElevationMap &map, const ElevationPoint &start, const ElevationPoint &end,
                   const ElevationMatrix<Distance> &dist, const ElevationPoint &u, const ElevationPath &shortest_path);
}
