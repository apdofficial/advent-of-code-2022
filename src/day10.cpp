#include "day10.hpp"

auto aoc2022::day10::parse_input(const std::vector<std::string> &lines) -> Instructions {
    Instructions instructions{};
    for (const auto &line: lines) {
        std::istringstream stream{line};
        std::string op_str{};
        stream >> op_str;
        if (op_str == "noop") {
            instructions.emplace_back(std::make_pair(InstructionType::noop, std::nullopt));
        } else if (op_str == "addx") {
            std::string val_str{};
            stream >> val_str;
            instructions.emplace_back(std::make_pair(InstructionType::addx, map_to_int(val_str)));
        }
    }
    return instructions;
}

auto aoc2022::day10::transform_to_signal_strengths(const CapturedRegisterValues &values) -> std::vector<int> {
    std::vector<int> signals{};
    std::ranges::transform(values, std::back_inserter(signals), [](const auto &value) {
        return value.first * value.second;
    });
    return signals;
}

auto aoc2022::day10::capture_register_x_values_if(const Instructions &instructions,
                                              std::function<bool(Cycle)> &&predicate) -> CapturedRegisterValues {
    Clock clock{};
    CPU cpu{};
    CapturedRegisterValues register_x_values{};

    cpu.load_instructions(instructions);

    clock.set_tick_callback([&cpu, &register_x_values, &predicate](auto cycle) {
        if (predicate(cycle)) {
            register_x_values.emplace_back(cycle, cpu.register_x());
        }
        cpu.advance();
    });

    while (!cpu.is_finished()) { clock.advance(); }

    return register_x_values;
}

auto aoc2022::day10::generate_crt_output(const Instructions &instructions) -> std::ostringstream {
    Clock clock{};
    CPU cpu{};
    CRT crt{};
    std::ostringstream crt_output;

    cpu.load_instructions(instructions);

    clock.set_tick_callback([&cpu, &crt](auto cycle) {
        crt.update(cycle, cpu.register_x());
        cpu.advance();
    });

    while (!cpu.is_finished()) { clock.advance(); }

    crt.print(crt_output);

    return crt_output;
}

void aoc2022::day10::CPU::load_instructions(const Instructions &instructions) {
    for(const auto& instruction : instructions) {
        cache_.emplace(instruction);
    };
}

auto aoc2022::day10::CPU::register_x() const -> RegisterValue {
    return register_x_;
}

void aoc2022::day10::CPU::advance() {
    if (is_finished()) return;
    auto [type, value] = cache_.front();
    if (available_in_ > 1) {
        --available_in_;
    } else if (available_in_ == 1) {
        --available_in_;
        if (type == InstructionType::addx) {
            register_x_ += value.value_or(0);
            cache_.pop();
        }
    } else {
        if (type == InstructionType::addx) {
            available_in_ += 1;
        } else if (type == InstructionType::noop) {
            cache_.pop();
        }
    }
}

bool aoc2022::day10::CPU::is_finished() const { return cache_.empty(); }

void aoc2022::day10::CRT::print(std::ostream &output) {
    for (int pixel: std::views::iota(0, n_pixels_)) {
        output << pixels_[pixel];
        if (pixel > 0 && ((pixel + 1) % width_  == 0)) output << '\n';
    }
}

void aoc2022::day10::CRT::update(Cycle cycle, int sprite_middle) {
    auto pixel = ((int) cycle % (n_pixels_ + 1)) - 1;
    auto pixel_x = (pixel % width_);
    auto should_turn_on = (sprite_middle - 1 <= pixel_x && pixel_x <= sprite_middle + 1);
    pixels_[pixel] = should_turn_on ? pixel_on_ : pixel_off_;
}

void aoc2022::day10::Clock::advance() {
    ++cycle_;
    tick_callback_(cycle_);
}

void aoc2022::day10::Clock::set_tick_callback(ClockTickCallback &&tick_callback) {
    tick_callback_ = std::move(tick_callback);
}
