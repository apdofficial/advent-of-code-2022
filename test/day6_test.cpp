#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day6.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc;

std::vector<std::pair<std::string, std::size_t>> short_packets_d6{
    {"mjqjpqmgbljsphdztnvjfqwrcgsmlb", 7},
    {"bvwbjplbgvbhsrlpgdmjqwftvncz", 5},
    {"nppdvjthqldpwncqszvftbrmjlhg", 6},
    {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 10},
    {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 11}
};

constexpr std::string_view DATA_PATH = "../../data/day6.txt";

TEST_CASE("Day 6, part 1 test") {
    for(const auto& [packet, expected_marker]: short_packets_d6) {
        std::istringstream packet_stream{packet};
        auto marker = day6::start_of_pocket_marker(packet_stream);
        REQUIRE(expected_marker == marker);
    }
}

TEST_CASE("Day 6, part 3 test") {
    REQUIRE(false);
}

TEST_CASE("Day 6 file (correctness)") {
    File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto marker = day6::start_of_pocket_marker(file.istream());
    REQUIRE(marker == 1080);
}