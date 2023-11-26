#include "day12.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day12;

std::vector<std::string> short_input_d12{"Sabqponm",
                                         "abcryxxl",
                                         "accszExk",
                                         "acctuvwj",
                                         "abdefghi"};

int part1(){
    auto elevation_map = parse_input(short_input_d12);
    auto start = find_start(elevation_map);
    auto end = find_end(elevation_map);
    auto shortest_path = find_shortest_path_dijkstra(elevation_map, start.value(), end.value(), true);
    fmt::println("Shortest path: {}", shortest_path.size());
    return 0;
}

int part2(){
    aoc::File file("../data/day12.txt");
    auto elevation_map = parse_input(file.read_lines());
    auto start = find_start(elevation_map);
    auto end = find_end(elevation_map);
    auto shortest_path = find_shortest_path_dijkstra(elevation_map, start.value(), end.value(), true);
    fmt::println("Shortest path: {}", shortest_path.size());
    return 0;
}

int main(){
//    part1();
    part2();
    return 0;
}