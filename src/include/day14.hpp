#pragma once

#include <iostream>

#include "util.h"


namespace aoc::day14 {
    static auto file_path = get_day_file_path(14);

    struct Coordinates {
        int x;
        int y;
    };

    struct Trace {

        Trace() = default;

        friend auto operator>>(std::istream& is, Trace& trace) -> std::istream& {
            std::string coord_str, delimiter, line;
            getline(is, line, '\n');
            std::istringstream iss(line);
            while(iss >> coord_str) {
                const auto split = coord_str.find(',');
                const auto x_str  = coord_str.substr(0, split);
                const auto y_str  = coord_str.substr(split+1, coord_str.size()-1);
                const auto x = map_to_int(x_str);
                const auto y = map_to_int(y_str);
                if(x && y) {
                    trace.path_.emplace_back(Coordinates{x.value(), y.value()});
                }
                iss >> delimiter;
            }
            return is;
        }

        friend auto operator<<(std::ostream& os, const Trace& trace) -> std::ostream& {
            for(const auto& [x, y] : trace.path_) {
                os << x << ", " << y << " -> ";
            }
            return os;
        }

        [[nodiscard]] auto path() const { return path_; }

    private:
        std::vector<Coordinates> path_;
    };

    struct Scan {

        Scan() = default;

        void append(Trace &&trace) {
            traces_.emplace_back(std::move(trace));
        }

        [[nodiscard]] auto traces() const { return traces_; }

    private:
        std::vector<Trace> traces_;
    };

    [[nodiscard]] auto parse_input(std::istream& stream, bool print = false) -> Scan;

    [[nodiscard]] auto part1(const Scan& scan) -> int;

    [[nodiscard]] auto part2(const Scan& scan) -> int;
}
