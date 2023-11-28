#pragma once

#include "util.h"
#include <queue>
#include <algorithm>
#include <ranges>
#include <sstream>
#include <iostream>
#include <functional>

namespace aoc::day10 {
    enum class InstructionType { addx, noop };

    using Cycle = unsigned long long;
    using RegisterValue = int;

    using InstructionValue = std::optional<int>;
    using Instruction = std::pair<InstructionType, InstructionValue>;
    using Instructions = std::vector<Instruction>;

    using CapturedRegisterValue = std::pair<Cycle, RegisterValue>;
    using CapturedRegisterValues = std::vector<CapturedRegisterValue>;

    using ClockTickCallback = std::function<void(Cycle)>;

    struct Clock {
        void set_tick_callback(ClockTickCallback&& tick_callback);

        void advance();

    private:
        ClockTickCallback tick_callback_;
        Cycle cycle_ = 0;
    };

    struct CRT {
        void print(std::ostream& output = std::cout);

        void update(Cycle cycle, int sprite_middle);

    private:
        static constexpr char pixel_on_ = '#';
        static constexpr char pixel_off_ = '.';
        static constexpr short width_ = 40;
        static constexpr short height_ = 6;
        static constexpr short n_pixels_ = width_ * height_;
        std::array<char, n_pixels_> pixels_{pixel_off_};
    };

    struct CPU {
        void load_instructions(const Instructions& instructions);

        void advance();

        [[nodiscard]] auto register_x() const -> RegisterValue;

        [[nodiscard]] bool is_finished() const;

    private:
        Cycle available_in_ = 0;
        RegisterValue register_x_ = 1;
        std::queue<Instruction> cache_{};
    };

    auto parse_input(const std::vector<std::string>& lines) -> Instructions;

    auto transform_to_signal_strengths(const CapturedRegisterValues& values) -> std::vector<int>;

    [[nodiscard]] auto capture_register_x_values_if(const Instructions& instructions,
                                                    std::function<bool(Cycle)>&& predicate) -> CapturedRegisterValues;

    [[nodiscard]] auto generate_crt_output(const Instructions& instructions) -> std::ostringstream;
}
