#include <day1/day1.hpp>

#include <iomanip>
#include <string_view>
#include <charconv>
#include <optional>
#include <span>
#include <iostream>
#include <vector>
#include <fstream>

constexpr std::string_view FILE_NAME = "day1.txt";

struct MyClass {
    struct InnerType {

    };

    auto function() -> InnerType;
};

auto MyClass::function() -> InnerType{
    return InnerType{};
}

auto stringToInt(std::string_view line) -> std::optional<int> {
    int converted_int;
    const auto result = std::from_chars(line.data(), line.data() + line.size(), converted_int);
    // Check for errors
    if (result.ec == std::errc::invalid_argument) {
        return std::nullopt;
    }
    return converted_int;
}


//int top_1_elf_calories(const std::vector<std::string>& lines) {
//    int max = 0;
//    std::accumulate(lines.begin(), lines.end(),0,[&max](auto accumulator, auto& line){
//        if (line.empty()){
//            if (accumulator > max) max = accumulator;
//            return 0;
//        }else return accumulator + stringToInt(line);
//    });
//    return max;
//}

// top_1_elf_calories: 69693
// Asymptotic analysis
// complexity is linear O(n)
// no redundant computation
auto top_1_elf_calories(const std::span<const std::string> lines) -> std::optional<int> {
    auto max_calories = 0;
    auto current_elf_calories = 0;
    for (const auto& line : lines) {
        if (line.empty()) {
            // Reached end one elf
            max_calories = std::max(current_elf_calories, max_calories);
            current_elf_calories = 0;
        } else {
            const auto parsed_value = stringToInt(line);
            if (!parsed_value) {
                return std::nullopt;
            }

            current_elf_calories += parsed_value.value();
        }
    }

    return max_calories;
}

// Asymptotic analysis
// complexity is linear O(n)
// no redundant computation
//int top_3_elf_calories(const std::vector<std::string> &lines) {
//    int max1 = 0, max2 = 0, max3 = 0;
//    std::accumulate(lines.begin(), lines.end(), 0, [&max1, &max2, &max3](auto accumulator, auto &line) {
//        if (line.empty()) {
//            if (accumulator > max1) {
//                if (max1 > max2) {
//                    if (max2 > max3) max3 = max2;
//                    max2 = max1;
//                }
//                max1 = accumulator;
//            } else if (accumulator > max2) {
//                if (max2 > max3) max3 = max2;
//                max2 = accumulator;
//            } else if (accumulator > max3) {
//                max3 = accumulator;
//            }
//            return 0;
//        } else return accumulator + stringToInt(line);
//    });
//    return max1 + max2 + max3;
//}

int run_day_1() {

    std::cout << "--Day " << 1 << " START--" << std::endl;
    std::ifstream file(FILE_NAME.data());
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(FILE_NAME) << "\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    std::cout << "top_1_elf_calories:       " << top_1_elf_calories(lines).value_or(0) << std::endl;
//    std::cout << "top_3_elf_calories:       " << top_3_elf_calories(lines) << std::endl;
    std::cout << "--Day " << 1 << " END--\n" << std::endl;
    return 0;
}