#include <functional>
#include "day5.hpp"

auto aoc::day5::parse_input(std::istream &is) -> std::pair<std::vector<Command>, std::vector<std::vector<char>>> {
    std::vector<std::vector<char>> stacks;
    std::vector<Command> commands;
    Command command{};
    std::string line;
    while (std::getline(is, line)) {
        if (line.starts_with("move")) { // command case
            std::istringstream iss(line);
            iss >> command;
            commands.push_back(command);
        } else { // stack case
            for (size_t i = 0; i < line.size(); i++) {
                if (isupper(line[i])) { // valid A-Z crate
                    size_t stack_nr = (i < 4 ? 0 : i / 4);
                    while (stacks.size() <= stack_nr) {
                        stacks.emplace_back();
                    }
                    stacks[stack_nr].push_back(line[i]);
                }
            }
        }
    }
    return std::make_pair(commands, stacks);
}

auto aoc::day5::execute_crane_9000(std::vector<std::vector<char>> &stacks, const std::vector<Command> &commands) -> void {
    for (const auto &command: commands) {
        for (size_t i = 0; i < command.crate_num + 1; i++) {
            stacks[command.to].push_back(stacks[command.from].back());
            stacks[command.from].pop_back();
        }
    }
}

auto aoc::day5::execute_crane_9001(std::vector<std::vector<char>> &stacks, const  std::vector<Command> &commands) -> void {
    for (const auto &command: commands) {
        auto iter = std::prev(stacks[command.from].end(), command.crate_num + 1);
        std::move(iter, stacks[command.from].end(), std::back_inserter(stacks[command.to]));
        for (size_t i = 0; i < command.crate_num + 1; i++)
            stacks[command.from].pop_back();
    }
}


//void run_day_5() {
//    std::string const fileName = "day" + DAY_NR + ".txt";
//    std::cout << "--Day " << DAY_NR << " START--" << std::endl;
//    std::ifstream file(fileName);
//    if (!file.is_open()) {
//        std::cerr << "Failed to open " << std::quoted(fileName) << "\n";
//        return 1;
//    }
//    std::vector<std::vector<char>> stacks_copy;
//
//    auto [commands, stacks] = parse_input(file);
//
//    for (auto &stack: stacks)
//        std::reverse(stack.begin(), stack.end());
//
//    stacks_copy = stacks;
//
//    execute_crane_9000(stacks, commands);
//
//    std::cout << "Top of each stack after using crane 9000: ";
//    for (auto &stack: stacks)
//        std::cout << stack.back();
//    std::cout << std::endl;
//
//    execute_crane_9001(stacks_copy, commands);
//
//    std::cout << "Top of each stack after using crane 9001: ";
//    for (auto &stack: stacks_copy)
//        std::cout << stack.back();
//
//    std::cout << std::endl;
//
//    std::cout << "--Day " << DAY_NR << " END--\n" << std::endl;
//    return;
//}


