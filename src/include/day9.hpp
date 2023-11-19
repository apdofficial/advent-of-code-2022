#pragma once

#include <algorithm>
#include <ranges>
#include <string>
#include "util.h"
#include <fmt/format.h>
#include <unordered_set>
#include <sstream>

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
            motion.magnitude = map_to_int(m).value_or(0);
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
    using Rope = std::vector<Position>;

    struct RopeSimulation {
        explicit RopeSimulation(unsigned rope_length);

        void move_head(const MotionDirection& direction);

        [[nodiscard]] auto tail_visited() const -> const Positions &;

    protected:
        void update_head_position(const MotionDirection& direction);

        static void follow_position(const Position& leader, Position& follower);

        auto head() -> Position&;

        auto tail() -> Position&;

    private:
        Rope rope_;
        Positions tail_visited_{};
    };

    auto parse_input(const std::vector<std::string>& lines) -> Motions;

    auto simulate_rope(const Motions &motions, unsigned rope_length) -> std::optional<RopeSimulation> ;
}