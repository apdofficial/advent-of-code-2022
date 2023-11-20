#include "day11.hpp"
#include "fmt/core.h"

aoc::day11::Monkey::Monkey(std::string &&monkey_str) {
    char delimiter = '\n';
    std::istringstream stream{std::move(monkey_str)};
    std::string line;
    while(getline(stream, line, delimiter)) {
        if(line.starts_with("Monkey")) continue;
        if(line.starts_with("  Starting items:")) {
            std::istringstream starting_items_str{line.substr(17, line.size())};
            std::string num_str{};
            while(starting_items_str >> num_str) {
                auto num = map_to_int(num_str);
                if(num.has_value()) {
                    items_.push_back(num.value());
                }
            }
        } else if(line.starts_with("  Operation:")) {
            std::istringstream line_Stream{line};
            std::string token1, new_str, eq_str, other_str, op_str, value_str;
            line_Stream >> token1 >> new_str >> eq_str >> other_str >> op_str >> value_str;
            int value = 0;
            if(value_str != "old") value = map_to_int(value_str).value_or(0);
            update_item_ = [=](Item item) {
                if(value_str == "old" && op_str == "*") return item * item;
                else if (op_str == "*") return item * value;
                else return item + value;
            };
        } else if(line.starts_with("  Test:")) {
            std::istringstream test_stream{line};
            std::string token1, op_str, token2, val_str;
            test_stream >> token1 >> op_str >> token2 >> val_str;
            int divisor = map_to_int(val_str).value_or(0);
            getline(stream, line, delimiter);
            unsigned monkey_id_if_true = map_to_int(line.substr(line.rfind("monkey") + 7, line.size())).value_or(0);
            getline(stream, line, delimiter);
            unsigned monkey_id_if_false = map_to_int(line.substr(line.rfind("monkey") + 7,line.size())).value_or(0);
            test_ = [=](Item item){
                if (item % divisor == 0) return std::make_pair(monkey_id_if_true, item);
                else return std::make_pair(monkey_id_if_false, item);
            };
        }
    }
}

void aoc::day11::Monkey::inspect_all_items() {
    inspection_counter_ += items_.size();
    std::ranges::transform(items_, items_.begin(), update_item_);
    std::ranges::transform(items_, items_.begin(), [](auto v){ return v / 3;});
}

void aoc::day11::Monkey::accept_item(Item item) {
    items_.push_back(item);
}

auto aoc::day11::Monkey::throw_item_to_other() -> std::optional<std::pair<MonkeyId, Item>> {
    if (!has_items()) return std::nullopt;
    auto item = items_.front();
    auto result = test_(item);
    items_.erase(items_.begin());
    return result;
}

auto aoc::day11::Monkey::has_items() const -> bool {return !items_.empty(); }

auto aoc::day11::Monkey::inspection_counter() const -> unsigned { return inspection_counter_; }

auto aoc::day11::parse_input(std::string &data) -> Monkeys {
    Monkeys monkeys{};
    std::string monkey_str{};
    std::string delimiter{"\n\n"};
    std::istringstream stream{std::move(monkey_str)};
    monkey_str = data.substr(0, data.find(delimiter)+delimiter.size());
    do {
        monkeys.emplace_back(std::move(monkey_str));
        data = data.substr(data.find(delimiter)+delimiter.size(), data.size());
        monkey_str = data.substr(0, data.find(delimiter)+delimiter.size());
    }while(!monkey_str.empty());
    return monkeys;
}

auto aoc::day11::monkey_business(Monkeys &monkeys, unsigned n_rounds) -> unsigned int {
    for(unsigned _: std::views::iota(0u, n_rounds)) {
        std::ranges::for_each(monkeys, [&monkeys](Monkey& monkey){
            monkey.inspect_all_items();
            while(monkey.has_items()) {
                auto [id, item] = monkey.throw_item_to_other().value();
                monkeys[id].accept_item(item);
            }
        });
    }
    std::ranges::sort(monkeys, std::greater{}, &Monkey::inspection_counter);
    return monkeys[0].inspection_counter() * monkeys[1].inspection_counter();
}