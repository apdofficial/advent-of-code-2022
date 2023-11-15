#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <array>

#include "day3.hpp"
#include "util.h"
#include "File.h"

using namespace aoc;

std::vector<std::string> short_list{"vJrwpWtwJgWrhcsFMMfFFhFp",
                                    "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
                                    "PmmdzqPrVvPwwTWBwg",
                                    "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
                                    "ttgJtRGJQctTZtZT",
                                    "CrZsJsPPZsGzwwsLwLmpwMDw"};

constexpr std::string_view DATA_PATH = "../../data/day3.txt";

TEST_CASE("Day 3, part 1 test") {
    REQUIRE(157 == day3::sum_item_priorities_of_both_compartments(short_list));
}

TEST_CASE("Day 3, part 2 test") {
    REQUIRE(70 == day3::sum_grouped_item_priorities_of_both_compartments(short_list));
}

TEST_CASE("Day 3 file (correctness)") {
    File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto list = file.read_lines();
    REQUIRE_FALSE(list.empty());

    REQUIRE(7917 == day3::sum_item_priorities_of_both_compartments(list));
    REQUIRE(2585 == day3::sum_grouped_item_priorities_of_both_compartments(list));
}

TEST_CASE("Day 3 file (performance)") {
    constexpr std::size_t n_runs{10000u};

    File file(DATA_PATH);
    auto list = file.read_lines();

    auto top_1_elf_calories_runtime = measure_average_runtime([&list]{
            day3::sum_item_priorities_of_both_compartments(list);
        }, n_runs).count();
    fmt::print("Average runtime performance sum_item_priorities_of_both_compartments: {} ms.\n", top_1_elf_calories_runtime);

    auto top_3_elf_calories_runtime = measure_average_runtime([&list]{
            day3::sum_grouped_item_priorities_of_both_compartments(list);
        }, n_runs).count();
    fmt::print("Average runtime performance sum_grouped_item_priorities_of_both_compartments: {} ms.\n", top_3_elf_calories_runtime);
}