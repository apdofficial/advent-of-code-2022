#include "day13.hpp"

auto aoc::day13::parse_input(std::istream& stream, bool print) -> Packets {
    Packets packets{};
    Packet packet{};
    while (stream >> packet) {
        packets.push_back(std::move(packet));
    }
    if(print) {
        std::size_t i = 1;
        for (const auto& pkt : packets) {
            std::cout << pkt << '\n';
            if(i % 2 == 0) std::cout << '\n';
            ++i;
        }
    }
    return packets;
}

auto aoc::day13::part1(const Packets& packets) -> std::size_t {
    if(packets.size() < 3) return 0;
    std::size_t index = 1;
    std::size_t sum = 0;
    for(std::size_t i = 0; i < packets.size() - 2; i += 2) {
        if (packets[i] < packets[i+1]) {
            sum += index;
        }
        ++index;
    }
    return sum;
}

auto aoc::day13::part2(const Packets& packets) -> std::size_t {
    auto packets_cpy = packets;

    std::sort(packets_cpy.begin(), packets_cpy.end());

    const auto first_iter = std::lower_bound(packets_cpy.begin(), packets_cpy.end(), Packet(PacketEntry{2}));
    const auto second_iter = std::lower_bound(packets_cpy.begin(), packets_cpy.end(),  Packet(PacketEntry{6}));

    const int first_idx = std::distance(packets_cpy.begin(), first_iter) + 1; // +1 for 0-indexing
    const int second_idx = std::distance(packets_cpy.begin(), second_iter) + 2; // +1 for 0-indexing, +1 for the second packet

    return first_idx * second_idx;
}
