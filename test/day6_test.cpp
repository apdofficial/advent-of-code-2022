#include <catch2/catch_all.hpp>
#include <fmt/format.h>

#include "day6.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc;

std::vector<std::string> short_packets_d6{{"mjqjpqmgbljsphdztnvjfqwrcgsmlb"},
                                          {"bvwbjplbgvbhsrlpgdmjqwftvncz"},
                                          {"nppdvjthqldpwncqszvftbrmjlhg"},
                                          {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"},
                                          {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"}};

constexpr std::string_view DATA_PATH = "../../data/day6.txt";

TEST_CASE("Day 6, part 1 test") {
    std::vector<std::size_t> expected_markers{7, 5, 6, 10, 11};
    for(std::size_t i = 0; i < expected_markers.size(); ++i) {
        std::istringstream packet_stream{short_packets_d6[i]};
        auto marker = day6::start_of_packet_marker(packet_stream);
        REQUIRE(expected_markers[i] == marker);
    }
}

TEST_CASE("Day 6, part 2 test") {
    std::vector<std::size_t> expected_markers{19, 23, 23, 29, 26};
    for(std::size_t i = 0; i < expected_markers.size(); ++i) {
        std::istringstream packet_stream{short_packets_d6[i]};
        auto marker = day6::start_of_message_marker(packet_stream);
        REQUIRE(expected_markers[i] == marker);
    }
}

TEST_CASE("Day 6 file (correctness)") {
    File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto start_of_packet_marker = day6::start_of_packet_marker(file.istream());
    fmt::println("start_of_packet_marker: {}", start_of_packet_marker);
    REQUIRE(start_of_packet_marker == 1080);

    auto start_of_message_marker = day6::start_of_message_marker(file.istream());
    REQUIRE(start_of_message_marker != 0);
    fmt::println("start_of_message_marker: {}", start_of_message_marker);
}