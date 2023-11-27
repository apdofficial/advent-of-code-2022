#pragma once

#include <istream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <span>
#include <optional>
#include <queue>
#include <algorithm>

namespace aoc::day06 {

    auto start_of_packet_marker(std::istream& packet) -> std::size_t;

    auto start_of_message_marker(std::istream& packet) -> std::size_t;
}