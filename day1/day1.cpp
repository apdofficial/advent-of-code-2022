#include "day1.h"

std::string const FILE_NAME = "day1.txt";

int stringToInt(const std::string& line){
    try {
        return stoi(line);
    }catch (std::invalid_argument& e){
        std::cout << "exception:" << e.what() << "for input: " << line << std::endl;
        return 0;
    }
}

std::vector<int> sumCaloriesOrdered(const std::vector<std::string> &lines) {
    std::vector<int> caloriesSum;
    std::accumulate(lines.begin(), lines.end(),0,[&caloriesSum](auto accumulator, auto& line){
        if (line.empty()) {
            caloriesSum.push_back(accumulator);
            return 0;
        }
        else return accumulator + stringToInt(line);
    });
    std::sort(caloriesSum.begin(), caloriesSum.end(), [](auto& lhs, auto& rhs){
        return lhs > rhs;
    });
    return caloriesSum;
}

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

int top_3_elf_calories(const std::vector<std::string>& lines) {
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;
    std::vector<int> caloriesSum;
    std::accumulate(lines.begin(), lines.end(),0,[&max1, &max2, &max3](auto accumulator, auto& line){
        if (line.empty()){
            if (accumulator > max1) {
                if (max1 > max2) {
                    if (max2 > max3) {
                        max3 = max2;
                    }
                    max2 = max1;
                }
                max1 = accumulator;
            }else if (accumulator > max2) {
                if (max2 > max3) {
                    max3 = max2;
                }
                max2 = accumulator;
            }else if (accumulator > max3) {
                max3 = accumulator;
            }
            return 0;
        }else{
            return accumulator + stringToInt(line);
        }
    });
    return max1 + max2 + max3;
}

int top_n_elf_calories(const std::vector<std::string>& lines, int n) {
    std::vector<int> caloriesSum = sumCaloriesOrdered(lines);
    auto end = caloriesSum.end();
    if (caloriesSum.size() > n) end = caloriesSum.begin() + n;
    return std::accumulate(caloriesSum.begin(), end, 0, [](auto accumulator, auto& sum){
        return accumulator + sum;
    });
}

int run_day_1() {
    std::cout << "--Day 1 START--" << std::endl;
    std::ifstream file(FILE_NAME);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(FILE_NAME) << "\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    std::cout << "top_1_elf_calories:       " << top_1_elf_calories(lines) << std::endl;
    std::cout << "top_n_elf_calories(1):    " << top_n_elf_calories(lines, 1) << std::endl;
    std::cout << "top_3_elf_calories:       " << top_3_elf_calories(lines) << std::endl;
    std::cout << "top_n_elf_calories(3):    " << top_n_elf_calories(lines, 3) << std::endl;
    std::cout << "--Day 1 END--\n" << std::endl;
    return 0;
}