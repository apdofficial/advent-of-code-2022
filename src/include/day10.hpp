#pragma once

#include "util.h"
#include <fmt/format.h>

namespace aoc::day10 {
    enum class Instruction{ addx, noop };

    using Instructions = std::vector<std::pair<Instruction, std::optional<int>>>;

    struct CPU{
        void process_instructions(const Instructions& instructions);

        [[nodiscard]] auto retrieve_register_x_values() const -> const std::vector<int>&;
    private:
        std::vector<int> register_x_values_{};
        int register_x_ = 1;
        unsigned long long cycle_ = 0;
    };

    auto parse_input(std::span<std::string> lines) -> Instructions;
}