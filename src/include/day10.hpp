#pragma once

#include "util.h"
#include <queue>
#include <tuple>

namespace aoc::day10 {
    enum class InstructionType {
        addx, noop
    };

    using Cycle = unsigned long long;
    using RegisterValue = int;

    using InstructionValue = std::optional<int>;
    using Instruction = std::pair<InstructionType, InstructionValue>;
    using Instructions = std::vector<Instruction>;

    using CapturedRegisterValue = std::pair<Cycle, RegisterValue>;
    using CapturedRegisterValues = std::vector<CapturedRegisterValue>;

    struct CRT{
        void print(std::ostream& output = std::cout);

        void update(Cycle cycle, int sprite_middle);

    private:
        static const short width_ = 40;
        static const short height_ = 6;
        std::array<char, 240> pixels_{'.'};
    };

    struct CPU {
        void process_instructions(const Instructions &instructions, CRT& crt);

        [[nodiscard]] auto retrieve_register_x_values() const -> const CapturedRegisterValues &;

    private:
        void advance_cycle(CRT &crt);

        CapturedRegisterValues register_x_values_{};
        RegisterValue register_x_ = 1;
        Cycle cycle_ = 0;
    };

    auto parse_input(const std::vector<std::string>& lines) -> Instructions;

    auto transform_to_signal_strengths(const CapturedRegisterValues& values) -> std::vector<int>;
}