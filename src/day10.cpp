#include "day10.hpp"

auto aoc::day10::parse_input(std::span<std::string> lines) -> Instructions{
    Instructions instructions{};
    for(const auto& line: lines){
        std::istringstream stream{line};
        std::string op_str{};
        stream >> op_str;
        if(op_str == "noop"){
            instructions.emplace_back(std::make_pair(Instruction::noop, std::nullopt));
        } else if (op_str == "addx") {
            std::string val_str{};
            stream >> val_str;
            instructions.emplace_back(std::make_pair(Instruction::addx, map_to_int(val_str)));
        }
    }
    return instructions;
}


void aoc::day10::CPU::process_instructions(const Instructions &instructions) {

}

auto aoc::day10::CPU::retrieve_register_x_values() const -> const std::vector<int>& {
    return register_x_values_;
}
