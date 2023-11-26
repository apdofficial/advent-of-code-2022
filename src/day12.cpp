#include <cassert>
#include "day12.hpp"
#include "fmt/color.h"

auto aoc::day12::parse_input(const std::vector<std::string> &data) -> ElevationMap {
    ElevationMap map{};
    for (int x = 0; x < data.size(); ++x) {
        map.emplace_back();
        for (int y = 0; y < data[x].size(); ++y) {
            map[x].emplace_back(data[x][y], x, y);
        }
    }
    return map;
}

auto aoc::day12::find_start(const ElevationMap &map) -> std::optional<ElevationPoint> {
    for (auto &row: map) {
        auto res = std::ranges::find_if(row, &ElevationPoint::is_start);
        if (res != row.end()) return *res;
    }
    return std::nullopt;
}

auto aoc::day12::find_end(const ElevationMap &map) -> std::optional<ElevationPoint> {
    for (auto &row: map) {
        auto res = std::ranges::find_if(row, &ElevationPoint::is_end);
        if (res != row.end()) return *res;
    }
    return std::nullopt;
}

auto aoc::day12::find_shortest_path_dijkstra(ElevationMap &map, const ElevationPoint &start,
                                             const ElevationPoint &end, bool visualise) -> ElevationPath {

    // current distance from the source to the vertex u
    Matrix<long long int> dist(map.size(), map[0].size(), 0);
    //  previous-hop nodes on the shortest path from source to the given vertex
    Matrix<std::optional<ElevationPoint>> prev(map.size(), map[0].size(), std::nullopt);
    // searches for the vertex u in the vertex set Q that has the least dist[u] value
    ElevationPath q{};
    // the shortest path from source to sink
    ElevationPath shortest_path{};
    constexpr int inf = std::numeric_limits<int>::max();

    for (std::size_t i = 0; i < map.size(); ++i) {
        for (std::size_t j = 0; j < map[i].size(); ++j) {
            if (map[i][j] != start) {
                dist[i][j] = inf;
                prev[i][j] = std::nullopt;
            }
            q.push_back(map[i][j]);
        }
    }
    dist[start] = 0;

    ElevationPoint u = q.back();
    while (!q.empty()) {
        std::ranges::sort(q, [&dist](const auto &a, const auto &b) { return dist[a] > dist[b]; });
        u = q.back();
        q.pop_back();
        for (auto &v: u.neighbours(map)) {
            if (!v.is_end() && std::ranges::find(q, v) == q.end()) continue; // already visited
            if (!v.is_end() && std::abs(v.height() - u.height()) > 1 && v.height() > u.height()) continue; // too high
            const auto alt = dist[u] + 1;
            if (alt < dist[v] || (v.is_end() && prev[end].value().height() < u.height()) ) {
                dist[v] = alt;
                prev[v] = u;
            }
        }
    }

    if (!prev[end].has_value()) return shortest_path;

    std::optional<ElevationPoint> u_opt = prev[end];
    while (u_opt.has_value()) {
        shortest_path.emplace_back(u_opt.value());
        if(!prev[u_opt.value()].has_value() && visualise){
            print_map(map, start, end, dist, u_opt.value(), shortest_path);
        }
        u_opt = prev[u_opt.value()];
    }
    return shortest_path;
}

void aoc::day12::print_map(const ElevationMap &map, const ElevationPoint &start, const ElevationPoint &end,
                           const Matrix<long long int> &dist, const ElevationPoint &u,
                           const ElevationPath &shortest_path) {
    for (std::size_t i = 0; i < map.size(); ++i) {
        for (std::size_t j = 0; j < map[i].size(); ++j) {
            if (i == start.x() && j == start.y()) {
                fmt::print(bg(fmt::color::black) | fg(fmt::color::white), "_S_ ");
            } else if (i == end.x() && j == end.y()) {
                fmt::print(bg(fmt::color::black) | fg(fmt::color::white), "_E_ ");
            } else if (u.x() == i && u.y() == j) {
                fmt::print("[X] ");
            } else {
                if (dist[i][j] == std::numeric_limits<int>::max()) fmt::print(fg(fmt::color::gray), "inf ");
                else {
                    auto found = std::ranges::find_if(shortest_path, [&map, &i, &j](const auto &item) {
                        return item == map[i][j];
                    }) != shortest_path.end();
                    if (found) {
                        fmt::print(bg(fmt::color::black) | fg(fmt::color::white), "{:03} ", dist[i][j]);
                    } else {
                        fmt::print(fg(fmt::color::gray), "{:03} ", dist[i][j]);
                    }
                }
            }
        }
        fmt::print("\n");
    }
    fmt::print("\n");
}
