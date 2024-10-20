#include "day06.hpp"

auto start_of_n_marker(std::istream &packet, size_t n_distinct_characters) -> std::size_t {
    std::vector<char> buffer;
    char tmp;
    for (std::size_t marker = 1; packet >> tmp; ++marker) {
        buffer.push_back(tmp);
        if (buffer.size() == n_distinct_characters) {
            auto found_marker = std::all_of(buffer.begin(), buffer.end(), [&buffer](auto c) {
                return std::count(buffer.begin(), buffer.end(), c) == 1;
            });
            if (found_marker) return marker;
            buffer.erase(buffer.begin());
        }
    }
    return 0;
}

auto aoc2022::day06::start_of_packet_marker(std::istream &packet) -> std::size_t {
    return start_of_n_marker(packet, 4);
}

auto aoc2022::day06::start_of_message_marker(std::istream &packet) -> std::size_t {
    return start_of_n_marker(packet, 14);
}
