#include "day5.hpp"

#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <span>

std::string const DAY_NR = "5";

struct Command {
    uint32_t crateNum;
    std::size_t from;
    std::size_t to;

    friend std::istream &operator>>(std::istream &s, Command &o) {
        std::string word;
        s >> word >> o.crateNum >> word >> o.from >> word >> o.to;
        --o.crateNum; // start form 0
        --o.from; // start form 0
        --o.to; // start form 0
        return s;
    }
};

void print_stacks(const std::vector<std::vector<char>> &stacks) {
    for (const auto &stack: stacks) {
        for (const auto &crate: stack) {
            std::cout << crate;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename T, std::size_t SIZE>
struct Array {};

struct Interface {
    virtual ~Interface() = default;
    virtual void func() {
        //
    }
};

class Interface2: Interface {
    // Private by default
    void func() {

    }

public:
    ~Interface2() {
        //
        Interface::func();
    }
};

struct Interface3 {
private:
    void func() {

    }
};

void create_interface_and_call() {
    Interface2 iface{};
    // Cannot call private function
    // iface.func();
}


struct BaseType : private Interface {
    void func() override {

    }
};
//
//template<typename StackCallback, typename CommandCallback>
//void parse_input(std::istream &s, StackCallback &&stack_callback, CommandCallback &&command_callback) {
//    std::string line;
//    Command command{};
//
//    while (std::getline(s, line)) {
//        if (line.starts_with("move")) { // command case
//            std::istringstream iss(line);
//            iss >> command;
//            command_callback(command);
//        } else { // stack case
//            for (size_t i = 0; i < line.size(); i++) {
//                if (isupper(line[i])) { // valid A-Z crate
//                    size_t stackNr = (i < 4 ? 0 : i / 4);
//                    stack_callback(stackNr, line[i]);
//                }
//            }
//        }
//    }
//}
//
//auto parse_input(std::istream &s) -> std::pair<std::vector<Command>, std::vector<std::vector<char>>> {
//    std::vector<std::vector<char>> stacks;
//    std::vector<Command> commands;
//    parse_input(s, [&stacks](std::size_t stack_nr, char character) {
//        if (stacks.size() <= stack_nr) {
//            stacks.emplace_back();
//        }
//        stacks[stack_nr].push_back(character);
//    }, [&commands](const Command &cmd) {
//        commands.push_back(cmd);
//    });
//    return std::make_pair(commands, stacks);
//}
//
//void execute_crane_9000(std::vector<std::vector<char>> &stacks, std::vector<Command> &commands) {
//    for (const auto &command: commands) {
//        for (size_t i = 0; i < command.crateNum + 1; i++) {
//            stacks[command.to].push_back(stacks[command.from].back());
//            stacks[command.from].pop_back();
//        }
//    }
//}
//
//void execute_crane_9001(std::vector<std::vector<char>> &stacks, std::vector<Command> &commands) {
//    for (const auto &command: commands) {
//        auto iter = std::prev(stacks[command.from].end(), command.crateNum + 1);
//        std::move(iter, stacks[command.from].end(), std::back_inserter(stacks[command.to]));
//        for (size_t i = 0; i < command.crateNum + 1; i++)
//            stacks[command.from].pop_back();
//    }
//}


void run_day_5() {
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
    return;
}


