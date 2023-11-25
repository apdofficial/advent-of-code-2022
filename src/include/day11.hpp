#pragma once

#include <queue>
#include <ranges>
#include <algorithm>
#include <fmt/core.h>
#include <regex>

#include "util.h"

namespace aoc::day11 {

    using MonkeyId = int;
    using Item = long long int;
    using TestWorryLevel = std::function<MonkeyId(Item)>;
    using CalculateWorryLevel = std::function<Item(Item)>;

    struct Monkey {
        explicit Monkey(std::string &&monkey_str);

        void inspect_all_items();

        [[nodiscard]] auto counter() const -> long long int;

        [[nodiscard]] auto test_divisor() const -> long long int;

        void set_worry_normaliser(std::function<Item(Item)> &&normaliser);

        std::vector<Item> items{};
        TestWorryLevel test;
    private:

        int test_divisor_ = 0;
        std::function<Item(Item)> normalise_item_ = [](auto v) { return v / 3; };

        CalculateWorryLevel update_item_;
        long long int counter_ = 0;

        void init_starting_items(std::istringstream &line);

        void init_operation(std::istringstream &line);

        void init_test(std::istringstream &stream, std::istringstream &line_stream);
    };

    using Monkeys = std::vector<Monkey>;

    [[nodiscard]] auto parse_input(std::string data) -> Monkeys;

    void simulate_rounds(Monkeys &monkeys, unsigned n_rounds);

    auto top_two_monkey_business(Monkeys &monkeys) ->  long long int;

    /**
     * @brief Set the normalised worry level for each monkey.
     *
     * @details Collect all test divisors and find the lowest common multiple.
     * Use it then to set the inspection divisor for each monkey.
     *
     * @param monkeys (output) The monkeys to set the normalised worry level for.
     */
    void set_normalised_worry(Monkeys &monkeys);
}
