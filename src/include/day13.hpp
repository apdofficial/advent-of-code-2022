#pragma once

#include <utility>
#include <fmt/format.h>
#include <iostream>
#include <algorithm>

#include "util.h"
#include "cassert"

namespace aoc::day13 {
    static auto file_path = get_day_file_path(13);

    struct PacketEntry {
        using Multi = std::vector<PacketEntry>;
        using Single = int;

        std::variant<Single, Multi> content;

        [[nodiscard]] auto is_single() const -> bool { return std::holds_alternative<Single>(content); }

        [[nodiscard]] auto is_multi() const -> bool { return std::holds_alternative<Multi>(content); }

        [[nodiscard]] auto single() const -> int { return std::get<Single>(content); }

        [[nodiscard]] auto multi() -> std::vector<PacketEntry>& { return std::get<Multi>(content); }

        [[nodiscard]] auto multi() const -> const std::vector<PacketEntry>& { return std::get<Multi>(content); }

        [[nodiscard]] auto emplace_multi() -> PacketEntry& {
            if (is_single()) transform_to_multi();
            multi().emplace_back(PacketEntry{.content = Multi{}});
            return multi().back();
        }

        void emplace_single(int val) {
            if (is_single()) transform_to_multi();
            multi().emplace_back(PacketEntry{.content = Single{val}});
        }

        void transform_to_multi() {
            if (is_single()) {
                content = Multi{PacketEntry{single()}};
            }
        }

        friend auto operator<=>(const Single lhs, const PacketEntry& rhs) {
            if (rhs.is_single()) return lhs <=> rhs.single();
            if (rhs.multi().empty()) return std::strong_ordering::greater;
            const auto cmp = lhs <=> rhs.multi().front();
            if (std::is_eq(cmp)) {
                if (rhs.multi().size() == 1) return std::strong_ordering::equal;
                return std::strong_ordering::less;
            }
            return cmp;
        }

        friend auto operator<=>(const PacketEntry& lhs, const Single rhs) {
            const auto cmp = rhs <=> lhs;
            if (std::is_lt(cmp)) return std::strong_ordering::greater;
            if (std::is_gt(cmp)) return std::strong_ordering::less;
            return std::strong_ordering::equal;
        }

        friend auto operator<=>(const PacketEntry& lhs, const PacketEntry& rhs) {
            if (lhs.is_single() && rhs.is_single()) {
                return lhs.single() <=> rhs.single();
            }
            if (lhs.is_single() && rhs.is_multi()) {
                return lhs.single() <=> rhs;
            }
            if (lhs.is_multi() && rhs.is_single()) {
                return lhs <=> rhs.single();
            }
            if (lhs.is_multi() && rhs.is_multi()) {
                auto left_iter = lhs.multi().begin();
                auto right_iter = rhs.multi().begin();
                while (true) {
                    if (left_iter == lhs.multi().end() && right_iter == rhs.multi().end()) return
                            std::strong_ordering::equal;
                    if (left_iter == lhs.multi().end()) return std::strong_ordering::less;
                    if (right_iter == rhs.multi().end()) return std::strong_ordering::greater;
                    if (auto cmp = *left_iter <=> *right_iter; !std::is_eq(cmp)) return cmp;
                    ++left_iter;
                    ++right_iter;
                }
            }
            return std::strong_ordering::equal;
        }

        friend std::ostream& operator<<(std::ostream& os, const PacketEntry& entry) {
            if (entry.is_single()) {
                os << std::format("{}", entry.single());
            } else {
                os << "[";
                std::string comma{""};
                for (auto& e: entry.multi()) {
                    os << comma << e;
                    comma = ",";
                }
                os << "]";
            }
            return os;
        }
    };

    struct Packet {

        explicit Packet() = default;

        explicit Packet(PacketEntry entry) : entry_{std::move(entry)} {}

        static void init_entries(std::istringstream& is, PacketEntry& entry) {
            char c;
            while (is) {
                is.get(c);
                if (is.eof()) return;
                if (c == '\n') return;
                if (c == single_delimiter) continue;
                if (c == multi_e_delimiter) return;
                if (c == multi_s_delimiter) {
                    init_entries(is, entry.emplace_multi());
                    continue;
                }
                if (std::isdigit(c)) {
                    std::string num_str{c};
                    while(std::isdigit(is.peek())) {
                        is.get(c);
                        num_str += c;
                    }
                    const auto num  = map_to_int(num_str);
                    if(num) entry.emplace_single(num.value());
                }
            }
        }

        friend std::istream& operator>>(std::istream& is, Packet& packet) {
            std::string line{};
            while (line.empty()) {
                if (!getline(is, line, '\n')) return is;
            }
            if (line.starts_with('[')) line.erase(0, 1);
            if (line.ends_with(']')) line.erase(line.size() - 1);
            std::istringstream line_stream{line};
            init_entries(line_stream, packet.entry_);
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, const Packet& packet) {
            os << packet.entry_;
            return os;
        }

        auto operator<=>(const Packet& rhs) const { return entry_ <=> rhs.entry(); }

        [[nodiscard]] auto entry() const -> const PacketEntry& { return entry_; }

    private:
        static constexpr char single_delimiter = ',';
        static constexpr char multi_s_delimiter = '[';
        static constexpr char multi_e_delimiter = ']';
        PacketEntry entry_{PacketEntry::Multi{}};
    };

    using Packets = std::vector<Packet>;

    [[nodiscard]] auto parse_input(std::istream& stream, bool print = false) -> Packets;

    [[nodiscard]] auto part1(const Packets& packets) -> std::size_t;

    [[nodiscard]] auto part2(const Packets& packets) -> std::size_t;
}
