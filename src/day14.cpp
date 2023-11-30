#include "day14.hpp"

#include <thread>

auto aoc::day14::parse_input(std::istream& stream, bool print) -> Scan {
    Scan scan{};
    Trace trace{};
    while (stream >> trace) {
        scan.append(std::move(trace));
    }
    if(print) {
        // for(auto& trc: scan.rock_traces()) {
        //     std::cout << trc << '\n';
        // }
        std::cout << scan << '\n';
    }
    scan.set_start(Scan::default_start);
    return scan;
}

auto aoc::day14::part1(const Scan& scan_, bool print) -> int {
    auto scan = scan_;
    int sand_num = 0;
    auto is_in_void = [&scan](const Coordinates& coord) {
        if(coord.col >= scan.bounding().max_col) return true;
        if(coord.col < scan.bounding().min_col) return true;
        if(coord.row > scan.bounding().max_row) return true;
        return false;
    };
    Coordinates current = Scan::default_start;
    while(!is_in_void(current)) {
        if(scan[current.row + 1][current.col] == Scan::air_char) { // down
            if (current != Scan::default_start) scan[current] = Scan::air_char;
            ++current.row;
            scan[current] = Scan::sand_char;
        } else if(scan[current.row + 1][current.col - 1] == Scan::air_char) { // down-lef
            scan[current] = Scan::air_char;
            ++current.row;
            --current.col;
            scan[current] = Scan::sand_char;
        } else if(scan[current.row + 1][current.col + 1] == Scan::air_char) { // down-rigt
            scan[current] = Scan::air_char;
            ++current.row;
            ++current.col;
            scan[current] = Scan::sand_char;
        } else {
            ++sand_num;
            current = Scan::default_start;
        }
    }
    if(print) std::cout << scan << '\n';
    return sand_num;
}

auto aoc::day14::part2(const Scan& scan_, bool print) -> int {
    auto scan = scan_;
    scan.set_floor(scan.bounding().max_row + 2);
    int sand_num = 0;
    auto reached_top = [](const Coordinates& coord) {
        return coord.col == Scan::default_start.col && coord.row == Scan::default_start.row;
    };
    Coordinates current = Scan::default_start;
     while(!reached_top(current)) {
        if(scan[current.row + 1][current.col] == Scan::air_char) { // down
            scan[current] = Scan::air_char;
            ++current.row;
            scan[current] = Scan::sand_char;
        } else if(scan[current.row + 1][current.col - 1] == Scan::air_char) { // down-lef
            scan[current] = Scan::air_char;
            ++current.row;
            --current.col;
            scan[current] = Scan::sand_char;
        } else if(scan[current.row + 1][current.col + 1] == Scan::air_char) { // down-rigt
            scan[current] = Scan::air_char;
            ++current.row;
            ++current.col;
            scan[current] = Scan::sand_char;
        } else {
            ++sand_num;
            current = Scan::default_start;
        }
    }
    if(print) std::cout << scan << '\n';
    return sand_num;
}
