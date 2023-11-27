#pragma once

#include <utility>
#include <fmt/format.h>

#include "util.h"
#include "common.hpp"
#include "cassert"

namespace aoc::day13 {

    auto file_path = get_day_file_path(13);

    struct PacketEntry {
        using Multi = std::vector<PacketEntry>;
        using Single = int;

        std::variant<Single, Multi> content;

        [[nodiscard]] auto is_single() const -> bool { return std::holds_alternative<Single>(content); }

        [[nodiscard]] auto is_multi() const -> bool { return std::holds_alternative<Multi>(content); }

        [[nodiscard]] auto single() const -> int { return std::get<Single>(content); }

        [[nodiscard]] auto multi() -> std::vector<PacketEntry> & { return std::get<Multi>(content); }

        [[nodiscard]] auto multi() const -> const std::vector<PacketEntry> & { return std::get<Multi>(content); }

        [[nodiscard]] auto emplace_multi() -> PacketEntry & {
            if (is_single()) transform_to_multi();
            multi().emplace_back(PacketEntry{.content=PacketEntry::Multi{}});
            return multi().back();
        }

        void set_single(int val) {
            content = PacketEntry::Single{val};
        }

        void transform_to_multi() {
            if (is_single()) {
                content = PacketEntry::Multi{std::vector<PacketEntry>{PacketEntry{single()}}};
            }
        }

        [[nodiscard]] static auto make_single() -> PacketEntry { return PacketEntry{.content=PacketEntry::Single{}}; }

        [[nodiscard]] static auto make_multi() -> PacketEntry { return PacketEntry{.content=PacketEntry::Multi{}}; }

        static constexpr void strip_start_end_tags(std::string &data, char s_tag = '[', char e_tag = ']') {
            if (data.starts_with(s_tag)) data.erase(0, 1);
            if (data.ends_with(e_tag)) data.erase(data.size() - 1);
        }
    };

    struct Packet {

        static void init_entries(std::istringstream &is, PacketEntry &entry) {
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
                    entry.set_single(c - '0');
                }
            }
        }

        friend std::istream &operator>>(std::istream &is, Packet &packet) {
            std::string line{};
            while (line.empty()) {
                if (!getline(is, line, '\n')) return is;
            }
            PacketEntry::strip_start_end_tags(line);
            std::istringstream line_stream{line};
            init_entries(line_stream, packet.entry_);
            return is;
        }

    private:
        static constexpr char single_delimiter = ',';
        static constexpr char multi_s_delimiter = '[';
        static constexpr char multi_e_delimiter = ']';
        PacketEntry entry_{std::vector<PacketEntry>{}};
    };

    using Packets = std::vector<Packet>;

    [[nodiscard]] auto parse_input(std::istream &stream) -> Packets {
        Packets packets{};
        Packet packet{};
        while (stream >> packet) {
            packets.push_back(std::move(packet));
        }
        return packets;
    }

    [[nodiscard]] auto part1(const Packets &packets) -> std::size_t {
        return 0;
    }

    [[nodiscard]] auto part2(const Packets &packets) -> std::size_t {
        return 0;
    }
}
