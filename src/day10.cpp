#include <algorithm>
#include <ranges>
#include "day10.hpp"

auto aoc::day10::parse_input(const std::vector<std::string> &lines) -> Instructions {
    Instructions instructions{};
    for (const auto &line: lines) {
        std::istringstream stream{line};
        std::string op_str{};
        stream >> op_str;
        if (op_str == "noop") {
            instructions.emplace_back(std::make_pair(InstructionType::noop, std::nullopt));
        } else if (op_str == "addx") {
            std::string val_str{};
            stream >> val_str;
            instructions.emplace_back(std::make_pair(InstructionType::addx, map_to_int(val_str)));
        }
    }
    return instructions;
}

auto aoc::day10::transform_to_signal_strengths(const CapturedRegisterValues &values) -> std::vector<int> {
    std::vector<int> signals{};
    std::ranges::transform(values, std::back_inserter(signals), [](const auto &value) {
        return value.first * value.second;
    });
    return signals;
}

void aoc::day10::CPU::process_instructions(const Instructions &instructions, CRT &crt) {
    for (const auto &[type, value]: instructions) {
        if (type == InstructionType::addx) {
            advance_cycle(crt);
            advance_cycle(crt);
            register_x_ += value.value_or(0);
        } else if (type == InstructionType::noop) {
            advance_cycle(crt);
        }
    }
}

void aoc::day10::CPU::advance_cycle(CRT &crt) {
    ++cycle_;
    if (cycle_ == 20 || (cycle_ >= 20 && (cycle_ - 20) % 40 == 0)) {
        register_x_values_.emplace_back(cycle_, register_x_);
    }
    crt.update(cycle_, register_x_);
}

auto aoc::day10::CPU::retrieve_register_x_values() const -> const CapturedRegisterValues & {
    return register_x_values_;
}

void aoc::day10::CRT::print(std::ostream &output) {
    for (int i: std::views::iota(0, height_)) {
        for (int j: std::views::iota(0, width_)) {
            output << pixels_[(width_*i)+j];
        }
        if(i != height_-1) output << "\n";
    }
}

void aoc::day10::CRT::update(Cycle cycle, int sprite_middle) {
    auto pixel = cycle - 1;
    auto pixel_x = (pixel % 40);
    if (sprite_middle - 1 <= pixel_x && pixel_x <= sprite_middle + 1) {
        pixels_[pixel] = '#';
    } else {
        pixels_[pixel] = '.';
    }
}
