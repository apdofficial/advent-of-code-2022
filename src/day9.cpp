#include "day9.hpp"

auto aoc::day9::details::map_to_direction(char c) -> std::optional<Direction> {
    if (c == 'R') return Direction::RIGHT;
    if (c == 'L') return Direction::LEFT;
    if (c == 'U') return Direction::UP;
    if (c == 'D') return Direction::DOWN;
    return std::nullopt;
}

auto aoc::day9::details::map_to_motion(std::string line) -> std::optional<Motion> {
    if(line.size() < 2) return std::nullopt;
    std::istringstream stream{line};
    char d, m;
    stream >> d >> m;
    auto direction = map_to_direction(d);
    auto magnitude = map_to_int(m);
    if(!direction.has_value() || !magnitude.has_value()) return std::nullopt;
    return Motion{direction.value(), magnitude.value()};
}

auto aoc::day9::parse_input(const std::vector<std::string> &lines) -> std::vector<Motion> {
    std::vector<Motion> motions{};
    std::ranges::copy(lines |
                std::views::transform(aoc::day9::details::map_to_motion) |
                std::views::filter([](auto o){ return o.has_value(); }) |
                std::views::transform([](auto o){ return o.value(); }),
            std::back_inserter(motions));
    return motions;
}

auto aoc::day9::count_tail_positions(const std::vector<Motion>& motions) -> unsigned {
    return 0;
}
