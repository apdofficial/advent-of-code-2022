#include "day12.hpp"


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

auto aoc::day12::find_shortest_path(ElevationMap &map, const ElevationPoint &start, const ElevationPoint &end,
                                    bool visualise) -> ElevationPath {
    // current distance from the source to the vertex u
    ElevationMatrix<Distance> dist(map.size(), map[0].size(), 0);
    // visited vertices
    ElevationMatrix<Visited> visited(map.size(), map[0].size(), Visited::FALSE);
    // previous-hop nodes on the shortest path from source to the given vertex
    ElevationMatrix<std::optional<ElevationPoint>> prev(map.size(), map[0].size(), std::nullopt);
    // SPT(Shortest Path Tree) (or the vertices for which the shortest distance is not finalized yet)
    std::vector<ElevationPoint> spt{}; // ideally we would use a priority queue based on fibonacci min heap (not in STL)
    // the shortest path from source to sink
    ElevationPath shortest_path{};

    constexpr int inf = std::numeric_limits<int>::max();

    for (std::size_t i = 0; i < map.size(); ++i) {
        for (std::size_t j = 0; j < map[i].size(); ++j) {
            if (map[i][j] != start) {
                dist[i][j] = inf;
                prev[i][j] = std::nullopt;
            }
            spt.emplace_back(map[i][j]);
        }
    }
    dist[start] = 0;

    auto u = spt.back();

    auto predicate = [&dist](const auto &a, const auto &b) -> auto { return dist[a] < dist[b]; };

    while (!spt.empty()) {
        // finding a min is current bottleneck, O(n) we could use a priority queue
        // implemented with a fibonacci min heap instead to make it O(log n)
        auto min = std::ranges::min_element(spt, predicate);
        u = *min;
        spt.erase(min);
        visited[u] = Visited::TRUE;
        for (auto &v: u.neighbours(map)) {
            if (!v.is_end() && visited[v] == Visited::TRUE) continue; // already visited
            if (!v.is_end() && std::abs(v.height() - u.height()) > 1 && v.height() > u.height()) continue; // too high
            const auto alt = dist[u] + 1;
            if (alt < dist[v] || (v.is_end() && prev[end].value().height() < u.height())) {
                dist[v] = alt;
                prev[v] = u;
            }
        }
    }

    if (!prev[end].has_value()) return shortest_path;

    std::optional<ElevationPoint> u_opt = prev[end];
    while (u_opt.has_value()) {
        shortest_path.emplace_back(u_opt.value());
        if (!prev[u_opt.value()].has_value() && visualise) {
            print_map(map, start, end, dist, u_opt.value(), shortest_path);
        }
        u_opt = prev[u_opt.value()];
    }

    return shortest_path;
}

auto aoc::day12::find_shortest_path_from_first_lowest(ElevationMap &map, const ElevationPoint &end,
                                                      bool visualise) -> ElevationPath {
    // current distance from the source to the vertex u
    ElevationMatrix<Distance> dist(map.size(), map[0].size(), 0);
    // visited vertices
    ElevationMatrix<Visited> visited(map.size(), map[0].size(), Visited::FALSE);
    // previous-hop nodes on the shortest path from source to the given vertex
    ElevationMatrix<std::optional<ElevationPoint>> prev(map.size(), map[0].size(), std::nullopt);
    // SPT(Shortest Path Tree) (or the vertices for which the shortest distance is not finalized yet)
    std::vector<ElevationPoint> spt{}; // ideally we would use a priority queue based on fibonacci min heap (not in STL)
    // the shortest path from source to sink
    ElevationPath shortest_path{};

    constexpr int inf = std::numeric_limits<int>::max();

    for (std::size_t i = 0; i < map.size(); ++i) {
        for (std::size_t j = 0; j < map[i].size(); ++j) {
            if (map[i][j] != end) {
                dist[i][j] = inf;
                prev[i][j] = std::nullopt;
            }
            spt.emplace_back(map[i][j]);
        }
    }
    dist[end] = 0;

    auto dist_predicate = [&dist](const auto &a, const auto &b) -> auto { return dist[a] < dist[b]; };
    auto height_predicate = [&dist](const auto &a, const auto &b) -> auto { return a.height() < b.height(); };

    std::optional<ElevationPoint> start = std::nullopt;

    auto end_neighbours = end.neighbours(map);
    auto max = std::ranges::max_element(end_neighbours, height_predicate);
    dist[*max] = 1;
    prev[*max] = end;

    auto min = std::ranges::min_element(spt, dist_predicate);
    ElevationPoint u = *min;

    while (!spt.empty()) {
        // finding a min is current bottleneck, O(n) we could use a priority queue
        // implemented with a fibonacci min heap instead to make it O(log n)
        min = std::ranges::min_element(spt, dist_predicate);
        u = *min;
        spt.erase(min);
        visited[u] = Visited::TRUE;
        if (u.is_end()) continue; // already visited (we don't want to visit the end)
        if (!start.has_value()) start = u;
        for (auto &v: u.neighbours(map)) {
            if (v.is_end() || visited[v] == Visited::TRUE) continue; // already visited
            if (std::abs(v.height() - u.height()) > 1 && v.height() < u.height()) continue; // too low
            const auto alt = dist[u] + 1;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
            }
            if (v.height() < start.value().height() && !v.is_start()) start = v;
        }
    }

    if (!start.has_value()) return shortest_path;
    if (!prev[start.value()].has_value()) return shortest_path;

    std::optional<ElevationPoint> u_opt = prev[start.value()];
    while (u_opt.has_value()) {
        shortest_path.emplace_back(u_opt.value());
        if (!prev[u_opt.value()].has_value() && visualise) {
            print_map(map, end, end, dist, u_opt.value(), shortest_path);
        }
        u_opt = prev[u_opt.value()];
    }

    return shortest_path;
}

void aoc::day12::print_map(const ElevationMap &map, const ElevationPoint &start, const ElevationPoint &end,
                           const ElevationMatrix<Distance> &dist, const ElevationPoint &u,
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
