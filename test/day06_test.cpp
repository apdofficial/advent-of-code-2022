#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day06.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc::day06;

std::vector<std::string> short_packets_d6{"mjqjpqmgbljsphdztnvjfqwrcgsmlb",
                                          "bvwbjplbgvbhsrlpgdmjqwftvncz",
                                          "nppdvjthqldpwncqszvftbrmjlhg",
                                          "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
                                          "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"};

constexpr std::string_view DATA_PATH = "../../data/day06.txt";

TEST_CASE("Day 06, part 1 test") {
    std::vector<std::size_t> expected_markers{7, 5, 6, 10, 11};
    for (std::size_t i = 0; i < expected_markers.size(); ++i) {
        std::istringstream packet_stream{short_packets_d6[i]};
        auto marker = start_of_packet_marker(packet_stream);
        REQUIRE(expected_markers[i] == marker);
    }
}

TEST_CASE("Day 06, part 2 test") {
    std::vector<std::size_t> expected_markers{19, 23, 23, 29, 26};
    for (std::size_t i = 0; i < expected_markers.size(); ++i) {
        std::istringstream packet_stream{short_packets_d6[i]};
        auto marker = start_of_message_marker(packet_stream);
        REQUIRE(expected_markers[i] == marker);
    }
}

TEST_CASE("Day 06 file (correctness)") {
    {
        aoc::File file(DATA_PATH);
        REQUIRE(file.is_valid());

        auto start_of_packet_marker_i = start_of_packet_marker(file.istream());
        fmt::println("start_of_packet_marker: {}", start_of_packet_marker_i);
        REQUIRE(start_of_packet_marker_i == 1080);
    }
    {
        aoc::File file(DATA_PATH);
        REQUIRE(file.is_valid());
        auto start_of_message_marker_i = start_of_message_marker(file.istream());
        fmt::println("start_of_message_marker: {}", start_of_message_marker_i);
        REQUIRE(start_of_message_marker_i == 3645);
    }
}