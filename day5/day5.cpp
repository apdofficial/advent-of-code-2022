#include "day5.h"

std::string const DAY_NR = "5";

void print_stacks(const std::vector<std::vector<char>>& stacks){
    for (const auto& stack:stacks) {
        for (const auto& crate:stack) {
            std::cout << crate;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void parse_input(std::istream& s, std::vector<std::vector<char>>& stacks, std::vector<Command>& commands){
    std::string line;
    Command command;
    while (std::getline(s, line)) {
        if (line.starts_with("move")) { // command case
            std::istringstream iss(line);
            iss >> command;
            commands.push_back(command);
        }else{ // stack case
            for (size_t i = 0; i < line.size(); i++) {
                if (isupper(line[i])){ // valid A-Z crate
                    size_t stackNr = ( i < 4 ? 0 : i/4);
                    if (stacks.size() <= stackNr) stacks.resize(stackNr+1);
                    stacks[stackNr].push_back(line[i]);
                }
            }
        }
    }
}

void execute_crane_9000(std::vector<std::vector<char>> &stacks, std::vector<Command>& commands){
    for (const auto& command : commands){
        for (size_t i = 0; i < command.crateNum + 1; i++){
            stacks[command.to].push_back(stacks[command.from].back());
            stacks[command.from].pop_back();
        }
    }
}

void execute_crane_9001(std::vector<std::vector<char>> &stacks, std::vector<Command>& commands){
    for (const auto& command : commands){
        auto iter = std::prev(stacks[command.from].end(), command.crateNum+1);
        std::move(iter, stacks[command.from].end(), std::back_inserter(stacks[command.to]));
        for (size_t i = 0; i < command.crateNum + 1; i++)
            stacks[command.from].pop_back();
    }
}


int run_day_5() {
    std::string const fileName = "day" + DAY_NR + ".txt";
    std::cout << "--Day " << DAY_NR << " START--" << std::endl;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(fileName) << "\n";
        return 1;
    }
    std::vector<std::vector<char>> stacks;
    std::vector<std::vector<char>> stacks_copy;
    std::vector<Command> commands;

    parse_input(file, stacks, commands);

    for (auto& stack: stacks)
        std::reverse(stack.begin(), stack.end());

    stacks_copy = stacks;

    execute_crane_9000(stacks, commands);

    std::cout << "Top of each stack after using crane 9000: ";
    for (auto& stack: stacks)
        std::cout << stack.back();
    std::cout << std::endl;

    execute_crane_9001(stacks_copy, commands);

    std::cout << "Top of each stack after using crane 9001: ";
    for (auto& stack: stacks_copy)
        std::cout << stack.back();

    std::cout << std::endl;

    std::cout << "--Day " << DAY_NR << " END--\n" << std::endl;
    return 0;
}


