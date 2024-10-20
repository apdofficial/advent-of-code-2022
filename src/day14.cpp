#include "day14.hpp"

#include <thread>

auto aoc2022::day14::parse_input(std::istream& stream, bool print) -> Scan {
    Scan scan{};
    Trace trace{};
    while (stream >> trace) {
        scan.append(std::move(trace));
    }
    if(print) std::cout << scan << '\n';
    scan.set_start(Scan::default_start);
    return scan;
}

auto aoc2022::day14::part1(const Scan& scan_, bool print) -> int {
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
        if(scan.map().at(current.row + 1, current.col) == Scan::CHAR_AIR) { // down
            if (current != Scan::default_start) scan.map()[current] = Scan::CHAR_AIR;
            ++current.row;
            scan.map()[current] = Scan::CHAR_SAND;
        } else if(scan.map().at(current.row + 1,current.col - 1) == Scan::CHAR_AIR) { // down-lef
            scan.map()[current] = Scan::CHAR_AIR;
            ++current.row;
            --current.col;
            scan.map()[current] = Scan::CHAR_SAND;
        } else if(scan.map().at(current.row + 1,current.col + 1) == Scan::CHAR_AIR) { // down-rigt
            scan.map()[current] = Scan::CHAR_AIR;
            ++current.row;
            ++current.col;
            scan.map()[current] = Scan::CHAR_SAND;
        } else {
            ++sand_num;
            current = Scan::default_start;
        }
    }
    if(print) std::cout << scan << '\n';
    return sand_num;
}

auto aoc2022::day14::part2(const Scan& scan_, bool print) -> int {
    auto scan = scan_;
    scan.set_floor(scan.bounding().max_row + 2);
    int sand_num = 0;
    auto reached_top = [](const Coordinates& coord) {
        return coord.col == Scan::default_start.col && coord.row == Scan::default_start.row;
    };
    Coordinates current = Scan::default_start;
     while(true) {
        if(scan.map().at(current.row + 1,current.col) == Scan::CHAR_AIR) { // down
            scan.map()[current] = Scan::CHAR_AIR;
            ++current.row;
            scan.map()[current] = Scan::CHAR_SAND;
        } else if(scan.map().at(current.row + 1,current.col - 1) == Scan::CHAR_AIR) { // down-lef
            scan.map()[current] = Scan::CHAR_AIR;
            ++current.row;
            --current.col;
            scan.map()[current] = Scan::CHAR_SAND;
        } else if(scan.map().at(current.row + 1,current.col + 1) == Scan::CHAR_AIR) { // down-rigt
            scan.map()[current] = Scan::CHAR_AIR;
            ++current.row;
            ++current.col;
            scan.map()[current] = Scan::CHAR_SAND;
        } else {
            ++sand_num;
            if(reached_top(current)) {
                scan.map()[Scan::default_start] = Scan::CHAR_SAND;
                break;
            }
            current = Scan::default_start;
        }
    }
    if(print) std::cout << scan << '\n';
    return sand_num;
}
