//
// Created by Andrej Pistek on 28/03/2023.
//

#include "FileDayProvider.h"

aoc::FileDayProvider::FileDayProvider(std::string_view file_path) :
        file{file_path}
{

}

auto aoc::FileDayProvider::provide_day() -> std::optional<aoc::DayPayload<int>>
{
    if (!file.is_valid()) return
    std::nullopt;
    auto lines = file.read_lines();
    DayPayload<int> day{lines};
    return day;
}