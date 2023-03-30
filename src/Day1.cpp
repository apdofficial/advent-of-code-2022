#include <numeric>
#include <ranges>

#include "Day1.hpp"
#include "util.h"

template<class T>
void aoc::Day1<T>::on_new(std::string_view line)
{
    this->dayPayload.lines.push_back(aoc::stooi(line));
}

template<class T>
void aoc::Day1<T>::on_lines_completed()
{
    this->dayPayload.answer1 = compute_top_1_elf_calories(this->dayPayload.lines);
    this->dayPayload.answer2 = compute_top_3_elf_calories_inplace(this->dayPayload.lines);
}




