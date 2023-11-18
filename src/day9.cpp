#include "day9.hpp"

auto aoc::day9::details::map_to_direction(char c) -> std::optional<Direction> {
    if (c == 'R') return Direction::RIGHT;
    if (c == 'L') return Direction::LEFT;
    if (c == 'U') return Direction::UP;
    if (c == 'D') return Direction::DOWN;
    return std::nullopt;
}

auto aoc::day9::details::map_to_motion(const std::pair<char, char> &raw_motion) -> std::optional<Motion> {
    auto direction = map_to_direction(raw_motion.first);
    auto magnitude = map_to_int(raw_motion.second);
    if(!direction.has_value() || !magnitude.has_value()) return std::nullopt;
    return Motion{direction.value(), magnitude.value()};
}

auto aoc::day9::parse_input(const std::vector<std::pair<char, char>> &raw_motions) -> std::vector<Motion> {
    std::vector<Motion> motions{};
    std::ranges::copy(raw_motions |
                std::views::transform(aoc::day9::details::map_to_motion) |
                std::views::filter([](auto o){ return o.has_value(); }) |
                std::views::transform([](auto o){ return o.value(); }),
            std::back_inserter(motions));
    return motions;
}

auto aoc::day9::count_tail_positions(const std::vector<Motion>& motions) -> unsigned {
    return 0;
}
