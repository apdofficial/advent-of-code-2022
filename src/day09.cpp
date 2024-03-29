#include "day09.hpp"

auto aoc::day09::parse_input(const std::vector<std::string>& lines) -> Motions {
    Motions motions{};
    std::ranges::transform(lines, std::back_inserter(motions), [](const auto& line){
        std::istringstream stream{line};
        Motion motion{};
        stream >> motion;
        return motion;
    });
    return motions;
}

auto aoc::day09::simulate_rope(const Motions &motions, unsigned rope_length) -> std::optional<RopeSimulation> {
    RopeSimulation simulation{rope_length};
    if(rope_length < 2) return std::nullopt;
    std::vector<Position> rope{rope_length, {0,0}};
    for (const auto& motion: motions) {
        for (int _ : std::views::iota(0, motion.magnitude)) {
            simulation.move_head(motion.direction);
        }
    }
    return simulation;
}

void aoc::day09::RopeSimulation::move_head(const MotionDirection& direction) {
    update_head_position(direction);
    for (unsigned i : std::views::iota(1u, rope_.size())) {
        follow_position(rope_[i-1], rope_[i]);
    }
    tail_visited_.insert(tail());
}

void aoc::day09::RopeSimulation::update_head_position(const MotionDirection& direction) {
    switch (direction) {
        case MotionDirection::UP: --head().y; break;
        case MotionDirection::DOWN: ++head().y; break;
        case MotionDirection::LEFT: --head().x; break;
        case MotionDirection::RIGHT: ++head().x; break;
    }
}

void aoc::day09::RopeSimulation::follow_position(const Position& leader, Position& follower) {
    if (std::abs(leader.x - follower.x) >= 2) {
        follower.x += (leader.x - follower.x) / 2;
        if (std::abs(leader.y - follower.y) >= 2)
            follower.y += (leader.y - follower.y) / 2;
        else
            follower.y += leader.y - follower.y;
    } else if (std::abs(leader.y - follower.y) >= 2) {
        follower.y += (leader.y - follower.y) / 2;
        follower.x += leader.x - follower.x;
    }
}

auto aoc::day09::RopeSimulation::tail_visited() const -> const Positions& {return tail_visited_;}

auto aoc::day09::RopeSimulation::head() -> Position & { return rope_.front();}

auto aoc::day09::RopeSimulation::tail() -> Position & {return rope_.back();}

aoc::day09::RopeSimulation::RopeSimulation(unsigned int rope_length): rope_(rope_length, {0, 0}) {}
