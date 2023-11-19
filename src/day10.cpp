#include <algorithm>
#include "day10.hpp"

auto aoc::day10::parse_input(const std::vector<std::string>& lines) -> Instructions {
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

auto aoc::day10::transform_to_signal_strengths(const CapturedRegisterValues& values) -> std::vector<int> {
    std::vector<int> signals{};
    std::ranges::transform(values, std::back_inserter(signals), [](const auto& value){
        return value.first * value.second;
    });
    return signals;
}

void aoc::day10::CPU::process_instructions(const Instructions &instructions) {
    for (const auto &[type, value]: instructions) {
        if(type == InstructionType::addx){
            advance_cycle();
            advance_cycle();
            register_x_ += value.value_or(0);
        } else if(type == InstructionType::noop){
            advance_cycle();
        }
    }
}

void aoc::day10::CPU::advance_cycle() {
    ++cycle_;
    if (cycle_ == 20 || (cycle_ >= 20 && (cycle_ - 20) % 40 == 0)) {
        register_x_values_.emplace_back(cycle_, register_x_);
    }
}

auto aoc::day10::CPU::retrieve_register_x_values() const -> const CapturedRegisterValues& {
    return register_x_values_;
}