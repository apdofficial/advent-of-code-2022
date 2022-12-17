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

void execute_commands(std::vector<std::vector<char>> &stacks, std::vector<Command>& commands){
    for (const auto& command : commands){
        for (size_t i = 0; i < command.crateNr+1; i++){
            stacks[command.to].push_back(stacks[command.from].back());
            stacks[command.from].pop_back();
        }
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
    std::vector<Command> commands;

    parse_input(file, stacks, commands);

    for (auto& stack: stacks)
        std::reverse(stack.begin(), stack.end());

    execute_commands(stacks, commands);

    print_stacks(stacks);

    std::cout << "Top of each stack after executing the commands: ";
    for (auto& stack: stacks)
        std::cout << stack.back();
    std::cout << std::endl;

    std::cout << "--Day " << DAY_NR << " END--\n" << std::endl;
    return 0;
}


