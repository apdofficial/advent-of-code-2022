#pragma once

#include <istream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <span>
#include <optional>

namespace aoc::day6 {

    auto start_of_packet_marker(std::istream& packet) -> std::size_t;

    auto start_of_message_marker(std::istream& packet) -> std::size_t;
}