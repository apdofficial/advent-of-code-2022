#include "day05.hpp"

auto aoc::day05::parse_input(std::istream &is) -> std::pair<std::vector<Command>, std::vector<std::vector<char>>> {
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
                    const std::size_t stack_nr = (i < 4 ? 0 : i / 4);
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

auto aoc::day05::execute_crane_9000(std::vector<std::vector<char>> &stacks, const std::vector<Command> &commands) -> void {
    for (const auto &[crate, from, to]: commands) {
        for (size_t i = 0; i < crate + 1; i++) {
            stacks[to].push_back(stacks[from].back());
            stacks[from].pop_back();
        }
    }
}

auto aoc::day05::execute_crane_9001(std::vector<std::vector<char>> &stacks, const  std::vector<Command> &commands) -> void {
    for (const auto &[crate, from, to]: commands) {
        const auto iter = std::prev(stacks[from].end(), crate + 1);
        std::move(iter, stacks[from].end(), std::back_inserter(stacks[to]));
        for (size_t i = 0; i < crate + 1; i++)
            stacks[from].pop_back();
    }
}
