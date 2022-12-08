#include "day1.h"

std::string const DAY_NR = "1";

int stringToInt(const std::string& line){
    try {
        return stoi(line);
    }catch (std::invalid_argument& e){
        std::cout << "exception:" << e.what() << "for input: " << line << std::endl;
        return 0;
    }
}

// complexity is linear O(n)
// no redundant computation
int top_1_elf_calories(const std::vector<std::string>& lines) {
    int max = 0;
    std::accumulate(lines.begin(), lines.end(),0,[&max](auto accumulator, auto& line){
        if (line.empty()){
            if (accumulator > max) max = accumulator;
            return 0;
        }else return accumulator + stringToInt(line);
    });
    return max;
}

// complexity is linear O(n)
// no redundant computation
int top_3_elf_calories(const std::vector<std::string>& lines) {
    int max1 = 0, max2 = 0, max3 = 0;
    std::accumulate(lines.begin(), lines.end(),0,[&max1, &max2, &max3](auto accumulator, auto& line){
        if (line.empty()){
            if (accumulator > max1) {
                if (max1 > max2) {
                    if (max2 > max3) max3 = max2;
                    max2 = max1;
                }
                max1 = accumulator;
            }else if (accumulator > max2) {
                if (max2 > max3) max3 = max2;
                max2 = accumulator;
            }else if (accumulator > max3) {
                max3 = accumulator;
            }
            return 0;
        }else return accumulator + stringToInt(line);
    });
    return max1 + max2 + max3;
}

int run_day_1() {
    std::string const fileName = "day" + DAY_NR + ".txt";
    std::cout << "--Day " << DAY_NR << " START--" << std::endl;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(fileName) << "\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    std::cout << "top_1_elf_calories:       " << top_1_elf_calories(lines) << std::endl;
    std::cout << "top_3_elf_calories:       " << top_3_elf_calories(lines) << std::endl;
    std::cout << "--Day " << DAY_NR << " END--\n" << std::endl;
    return 0;
}