#include "day9.hpp"

auto aoc::day9::parse_input(const std::vector<std::string>& lines) -> Motions {
    Motions motions{};
    std::ranges::transform(lines, std::back_inserter(motions), [](const auto& line){
        std::istringstream stream{line};
        Motion motion{};
        stream >> motion;
        return motion;
    });
    return motions;
}

auto aoc::day9::simulate_rope(const Motions &motions) -> RopeSimulation {
    RopeSimulation simulation{};
    for (const auto& motion: motions) {
        for (int _ : std::views::iota(0, motion.magnitude)) {
            simulation.move_head(motion.direction);
        }
    }
    return simulation;
}

void aoc::day9::RopeSimulation::move_head(const MotionDirection& direction) {
    update_head_position(direction);
    update_tail_position();
}

void aoc::day9::RopeSimulation::update_head_position(const MotionDirection& direction) {
    switch (direction) {
        case MotionDirection::UP: --head_.y; break;
        case MotionDirection::DOWN: ++head_.y; break;
        case MotionDirection::LEFT: --head_.x; break;
        case MotionDirection::RIGHT: ++head_.x; break;
    }
}

void aoc::day9::RopeSimulation::update_tail_position() {
    if (std::abs(head_.x - tail_.x) >= 2) {
        tail_.x += (head_.x - tail_.x) / 2;
        if (std::abs(head_.y - tail_.y) >= 2)
            tail_.y += (head_.y - tail_.y) / 2;
        else
            tail_.y += head_.y - tail_.y;
    } else if (std::abs(head_.y - tail_.y) >= 2) {
        tail_.y += (head_.y - tail_.y) / 2;
        tail_.x += head_.x - tail_.x;
    }
    tail_visited_.insert(tail_);
}

auto aoc::day9::RopeSimulation::tail_visited() const -> const Positions& {return tail_visited_;}
