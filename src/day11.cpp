#include "day11.hpp"

auto operation(const std::string &op, const aoc::day11::Item &a, const aoc::day11::Item &b) -> aoc::day11::Item {
    if (op == "*") {
        return a * b;
    } else if (op == "+") {
        return a + b;
    } else if (op == "-") {
        return a - b;
    } else if (op == "/") {
        if (b == 0) return 0;
        return a / b;
    } else {
        return a;
    }
}

auto aoc::day11::parse_input(std::string data) -> Monkeys {
    Monkeys monkeys{};
    std::string delimiter{"\n\n"};
    std::string monkey_str{data.substr(0, data.find(delimiter) + delimiter.size())};
    while (monkey_str.size() > 1) {
        monkeys.emplace_back(std::move(monkey_str));
        data = data.substr(data.find(delimiter) + delimiter.size(), data.size());
        monkey_str = data.substr(0, data.find(delimiter) + delimiter.size());
    }
    return monkeys;
}

void aoc::day11::simulate_rounds(Monkeys &monkeys, unsigned n_rounds) {
    for (auto i: std::views::iota(0u, n_rounds)) {
        std::ranges::for_each(monkeys, [&monkeys](Monkey &monkey) {
            monkey.inspect_all_items();
            for(auto item: monkey.items) {
                auto id = monkey.test(item);
                monkeys[id].items.push_back(item);
            }
            monkey.items.clear();
        });
    }
}

void aoc::day11::set_normalised_worry(Monkeys &monkeys) {
    long long int strategical_divisor = std::accumulate(monkeys.begin(), monkeys.end(), 1, [](auto acc, auto &monkey) {
        return acc * monkey.test_divisor();
    });
    std::ranges::for_each(monkeys, [&strategical_divisor](auto &monkey) {
        monkey.set_worry_normaliser([=](auto v) { return v % strategical_divisor; });
    });
}

auto aoc::day11::top_two_monkey_business(aoc::day11::Monkeys &monkeys) -> long long int {
    std::ranges::sort(monkeys, std::greater{}, &Monkey::counter);
    return monkeys[0].counter() * monkeys[1].counter();
}

aoc::day11::Monkey::Monkey(std::string &&monkey_str) {
    std::istringstream stream{std::move(monkey_str)};
    std::string line;
    while (getline(stream, line)) {
        std::istringstream line_stream{line};
        if (line.starts_with("Monkey")) continue;
        if (line.starts_with("  Starting items:")) init_starting_items(line_stream);
        else if (line.starts_with("  Operation:")) init_operation(line_stream);
        else if (line.starts_with("  Test:")) init_test(stream, line_stream);
    }
}

void aoc::day11::Monkey::init_test(std::istringstream &stream, std::istringstream &line_stream) {
    std::string token1, op_str, token2, val_str, line;
    line_stream >> token1 >> op_str >> token2 >> val_str;
    test_divisor_ = map_to_int(val_str).value_or(0);
    getline(stream, line);
    int a = map_to_int(line.substr(line.rfind("monkey") + 7, line.size())).value_or(0);
    getline(stream, line);
    int b = map_to_int(line.substr(line.rfind("monkey") + 7, line.size())).value_or(0);
    test = [=, divisor=test_divisor_](Item item) {
        if (item % divisor == 0) return a;
        else return b;
    };
}

void aoc::day11::Monkey::init_operation(std::istringstream &line) {
    std::string token1, new_str, eq_str, other_str, op_str, value_str;
    line >> token1 >> new_str >> eq_str >> other_str >> op_str >> value_str;
    auto num = map_to_int(value_str);
    update_item_ = [=](Item item) { return operation(op_str, item, num.value_or(item)); };
}

void aoc::day11::Monkey::init_starting_items(std::istringstream &line) {
    for (std::string num_str{}; line >> num_str;) {
        auto num = map_to_int(num_str);
        if (num.has_value()) items.push_back(num.value());
    }
}

void aoc::day11::Monkey::inspect_all_items() {
    counter_ += items.size();
    std::ranges::transform(items, items.begin(), update_item_);
    std::ranges::transform(items, items.begin(), normalise_item_);
}

auto aoc::day11::Monkey::counter() const -> long long int { return counter_; }

void aoc::day11::Monkey::set_worry_normaliser(std::function<Item(Item)> &&normaliser) { normalise_item_ = std::move(normaliser); }

auto aoc::day11::Monkey::test_divisor() const -> long long int { return test_divisor_; }