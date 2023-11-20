#pragma once

#include <queue>
#include <ranges>
#include <algorithm>

#include "util.h"

namespace aoc::day11 {

    using MonkeyId = int;
    using Item = int;
    using TestWorryLevel = std::function<std::pair<MonkeyId, Item>(Item)>;
    using CalculateWorryLevel = std::function<Item(Item)>;

    struct Monkey{
        explicit Monkey(std::string&& monkey_str);

        void inspect_all_items();

        void accept_item(Item item);

        [[nodiscard]] auto throw_item_to_other() -> std::optional<std::pair<MonkeyId, Item>>;

        [[nodiscard]] auto has_items() const -> bool;

        [[nodiscard]] auto inspection_counter() const -> unsigned;
        std::vector<Item> items_{}; // NOLINT
    private:

        TestWorryLevel test_;
        CalculateWorryLevel update_item_;
        unsigned inspection_counter_ = 0;
    };

    using Monkeys = std::vector<Monkey>;

    [[nodiscard]] auto parse_input(std::string& data) -> Monkeys;

    [[nodiscard]] auto monkey_business(Monkeys& monkeys, unsigned n_rounds) -> unsigned;
}