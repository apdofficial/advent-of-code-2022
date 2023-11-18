#pragma once

#include <algorithm>
#include <ranges>
#include <string>
#include "util.h"
#include <fmt/format.h>
#include <unordered_set>

namespace aoc::day9 {
    enum class MotionDirection {
        UP, DOWN, LEFT, RIGHT
    };

    struct Motion {
        MotionDirection direction;
        int magnitude;

        friend std::istream& operator>>(std::istream &is, Motion& motion) {
            char d{};
            std::string m{};
            is >> d >> m;
            if (d == 'R') motion.direction = MotionDirection::RIGHT;
            if (d == 'L') motion.direction = MotionDirection::LEFT;
            if (d == 'U') motion.direction = MotionDirection::UP;
            if (d == 'D') motion.direction = MotionDirection::DOWN;
            auto magnitude_optional = map_to_int(m);
            if (!magnitude_optional.has_value()) throw std::runtime_error("could not parse magnitude");
            motion.magnitude = magnitude_optional.value();
            return is;
        }
    };

    using Motions = std::vector<Motion>;

    struct Position {
        int x;
        int y;

        friend auto operator<=>(const Position &, const Position &) = default;
    };

    struct PositionHash {
        size_t operator()(const Position &pos) const {
            return std::hash<int>{}(pos.x) ^ (std::hash<int>{}(pos.y) << 1);
        }
    };

    using Positions = std::unordered_set<Position, PositionHash>;

    struct RopeSimulation {

        void move_head(const MotionDirection& direction);

        [[nodiscard]] auto tail_visited() const -> const Positions &;

    protected:
        void update_head_position(const MotionDirection& direction);

        void update_tail_position();

    private:
        Positions tail_visited_{};
        Position head_{};
        Position tail_{};
    };

    auto parse_input(const std::vector<std::string>& lines) -> Motions;

    auto simulate_rope(const Motions &motions) -> RopeSimulation;
}