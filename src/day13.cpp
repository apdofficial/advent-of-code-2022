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
    return 0;
}
