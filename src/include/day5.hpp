#pragma once

#include <istream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <span>
#include <functional>

namespace aoc::day5 {
    struct Command {
        uint32_t crate_num;
        std::size_t from;
        std::size_t to;

        friend std::istream &operator>>(std::istream &s, Command &o) {
            std::string word;
            s >> word >> o.crate_num >> word >> o.from >> word >> o.to;
            --o.crate_num; // start form 0
            --o.from; // start form 0
            --o.to; // start form 0
            return s;
        }
    };

    auto print_stacks(const std::vector<std::vector<char>> &stacks, std::ostream& output = std::cout) -> void;

    auto parse_input(std::istream &s) -> std::pair<std::vector<Command>, std::vector<std::vector<char>>>;

    auto execute_crane_9000(std::vector<std::vector<char>> &stacks, const std::vector<Command> &commands) -> void;

    auto execute_crane_9001(std::vector<std::vector<char>> &stacks, const std::vector<Command> &commands) -> void;
}