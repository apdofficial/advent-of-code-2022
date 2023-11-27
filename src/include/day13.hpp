#pragma once

#include <utility>
#include <fmt/format.h>

#include "util.h"
#include "common.hpp"

namespace aoc::day13 {

    using EntryType = int;
    using SingleEntry = EntryType;
    using VectorEntry = std::vector<EntryType>;
    using PacketEntry = std::variant<SingleEntry, VectorEntry>;
    using PacketData = std::vector<PacketEntry>;

    using Index = int;

    namespace details {
        void strip_start_end_tags(std::string &data, char s_tag = '[', char e_tag = ']') {
            if (data.find(s_tag) == 0) data.erase(0, 1);
            if (data.rfind(e_tag) == data.size() - 1) data.erase(data.size() - 1);
        }
    }

    struct Packet {
        explicit Packet(std::string data): data_{} {
            details::strip_start_end_tags(data);
            std::stringstream ss_data{data};

            fmt::println("data: {}", data);
            std::vector<std::string> str_entries{};

            std::string str_entry{};
            while (getline(ss_data, str_entry, ',')) {
                fmt::println("str_entry: {}", str_entry);
                
            }
        }

        [[nodiscard]] auto data() const -> const PacketData & { return data_; }

    private:
        PacketData data_;
    };

    struct PacketPair {
        Packet left;
        Packet right;
        Index index = 0;
    };

    using PacketPairs = std::vector<PacketPair>;

    [[nodiscard]] auto parse_input(const InputLines &lines) -> PacketPairs {
        PacketPairs packets_pairs{};
        Index line_idx = 0;
        Index packet_idx = 1;
        while (line_idx < lines.size()) {
            auto &line_left = lines[line_idx];
            if (line_left.empty()) {
                ++line_idx;
                continue;
            }
            if (line_idx + 1 > lines.size()) break;
            auto &line_right = lines[line_idx + 1];
            fmt::println("{} | {}", line_left, line_right);
            packets_pairs.emplace_back(PacketPair{Packet{line_left}, Packet{line_right}, packet_idx});
            ++packet_idx;
            line_idx += 2;
        }
        return packets_pairs;
    }

    [[nodiscard]] auto part1(const PacketPairs &packet_pairs) -> std::size_t {
        return 0;
    }

    [[nodiscard]] auto part2(const PacketPairs &packet_pairs) -> std::size_t {
        return 0;
    }
}
