#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day12.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day12;


std::vector<std::string> short_input_d12{"Sabqponm",
                                         "abcryxxl",
                                         "accszExk",
                                         "acctuvwj",
                                         "abdefghi"};

constexpr std::string_view DATA_PATH = "../../data/day12.txt";

TEST_CASE("Day 12, part 1 test") {
    auto elevation_map = parse_input(short_input_d12);
    auto start = find_start(elevation_map);
    REQUIRE(start.has_value());
    auto end = find_end(elevation_map);
    REQUIRE(end.has_value());
    auto shortest_path = find_shortest_path_dijkstra(elevation_map, start.value(), end.value());
    REQUIRE(shortest_path.size() == 31);
}

TEST_CASE("Day 12, part 2 test") {
    REQUIRE(false);
}

TEST_CASE("Day 12 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());
    auto input = file.read_lines();
    auto elevation_map = parse_input(input);
    auto start = find_start(elevation_map);
    REQUIRE(start.has_value());
    auto end = find_end(elevation_map);
    REQUIRE(end.has_value());
    auto shortest_path = find_shortest_path_dijkstra(elevation_map, start.value(), end.value());
    fmt::println("Shortest path: {}", shortest_path.size());
    REQUIRE(shortest_path.size() == 437);
}