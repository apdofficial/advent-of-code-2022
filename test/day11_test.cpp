#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <ranges>

#include "day11.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day11;


std::string short_input_d11{"Monkey 0:\n"
                            "  Starting items: 79, 98\n"
                            "  Operation: new = old * 19\n"
                            "  Test: divisible by 23\n"
                            "    If true: throw to monkey 2\n"
                            "    If false: throw to monkey 3\n"
                            "\n"
                            "Monkey 1:\n"
                            "  Starting items: 54, 65, 75, 74\n"
                            "  Operation: new = old + 6\n"
                            "  Test: divisible by 19\n"
                            "    If true: throw to monkey 2\n"
                            "    If false: throw to monkey 0\n"
                            "\n"
                            "Monkey 2:\n"
                            "  Starting items: 79, 60, 97\n"
                            "  Operation: new = old * old\n"
                            "  Test: divisible by 13\n"
                            "    If true: throw to monkey 1\n"
                            "    If false: throw to monkey 3\n"
                            "\n"
                            "Monkey 3:\n"
                            "  Starting items: 74\n"
                            "  Operation: new = old + 3\n"
                            "  Test: divisible by 17\n"
                            "    If true: throw to monkey 0\n"
                            "    If false: throw to monkey 1\n"
                            "\n"};

constexpr std::string_view DATA_PATH = "../../data/day11.txt";

TEST_CASE("Day 11, part 1 test") {
    auto monkeys = parse_input(short_input_d11);
    simulate_rounds(monkeys, 20u);
    REQUIRE(top_two_monkey_business(monkeys) == 10605);
}

TEST_CASE("Day 11, part 2 test") {
    auto monkeys = parse_input(short_input_d11);
    set_normalised_worry(monkeys);
    simulate_rounds(monkeys, 10000u);
    REQUIRE(top_two_monkey_business(monkeys) == 2713310158);
}

TEST_CASE("Day 11 file (correctness)") {
    aoc::File file(DATA_PATH);
    REQUIRE(file.is_valid());
    auto input = file.read_string();

    auto monkeys = parse_input(input);
    simulate_rounds(monkeys, 20u);
    REQUIRE(top_two_monkey_business(monkeys) == 90294);

    monkeys = parse_input(input);
    set_normalised_worry(monkeys);
    simulate_rounds(monkeys, 10000u);
    REQUIRE(top_two_monkey_business(monkeys) == 18170818354);
}