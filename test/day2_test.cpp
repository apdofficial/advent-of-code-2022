#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <array>

#include "day2.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc;

std::vector<std::pair<char, char>> short_rounds{{'A', 'Y'},
                                                {'B', 'X'},
                                                {'C', 'Z'}};

constexpr std::string_view DATA_PATH = "../../data/day2.txt";

TEST_CASE("Day 2, part 1 test") {
    REQUIRE(15 == day2::calculate_strategy_score(short_rounds));
}

TEST_CASE("Day 2, part 2 test") {
    REQUIRE(12 == day2::calculate_new_strategy_score(short_rounds));
}

TEST_CASE("Day 2 file (correctness)") {
    File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto rounds = file.read_pairs();
    REQUIRE_FALSE(rounds.empty());

    REQUIRE(13526 == day2::calculate_strategy_score(rounds));
    REQUIRE(14204 == day2::calculate_new_strategy_score(rounds));
}

TEST_CASE("Day 2 file (performance)") {
    constexpr std::size_t n_runs{10000u};

    File file(DATA_PATH);
    auto rounds = file.read_pairs();

    auto top_1_elf_calories_runtime = measure_runtime([&rounds] {
        day2::calculate_strategy_score(rounds);
    }, n_runs).count();
    fmt::print("Average runtime performance calculate_strategy_score: {} ms.\n", top_1_elf_calories_runtime);

    auto top_3_elf_calories_runtime = measure_runtime([&rounds] {
        day2::calculate_new_strategy_score(rounds);
    }, n_runs).count();
    fmt::print("Average runtime performance calculate_new_strategy_score: {} ms.\n", top_3_elf_calories_runtime);
}