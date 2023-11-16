#include <queue>
#include "day6.hpp"

auto aoc::day6::start_of_pocket_marker(std::istream& packet) -> std::size_t {
    std::size_t marker = 0;
    std::vector<char> buffer;
    char tmp;
    for(;packet >> tmp; ++marker) {
        buffer.push_back(tmp);
        if(buffer.size() == 4) {
            auto a = buffer[0] != buffer[1] && buffer[0] != buffer[2] && buffer[0] != buffer[3];
            auto b = buffer[1] != buffer[2] && buffer[1] != buffer[3];
            auto c = buffer[2] != buffer[3];
            if (a && b && c) break;
            buffer.erase(buffer.begin());
        }
    }
    return marker + 1;
}