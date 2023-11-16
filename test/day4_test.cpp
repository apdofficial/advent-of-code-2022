#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <array>

#include "day4.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc;

std::vector<std::string> short_lines_d4{"2-4,6-8",
                                      "2-3,4-5",
                                      "5-7,7-9",
                                      "2-8,3-7",
                                      "6-6,4-6",
                                      "2-6,4-8"};

auto short_ranges = day4::map_to_ranges(short_lines_d4);

constexpr std::string_view DATA_PATH = "../../data/day4.txt";

TEST_CASE("Day 4, part 1 test") {
    REQUIRE(2 == day4::num_of_fully_contained_ranges(short_ranges));
}

TEST_CASE("Day 4, part 2 test") {
    REQUIRE(4 == day4::num_of_overlapping_ranges(short_ranges));
}

TEST_CASE("Day 4 file (correctness)") {
    File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto lines = file.read_lines();
    auto ranges = day4::map_to_ranges(lines);
    REQUIRE_FALSE(ranges.empty());

    REQUIRE(651 == day4::num_of_fully_contained_ranges(ranges));
    REQUIRE(956 == day4::num_of_overlapping_ranges(ranges));
}

TEST_CASE("Day 4 file (performance)") {
    constexpr std::size_t n_runs{10000u};

    File file(DATA_PATH);
    auto lines = file.read_lines();
    auto ranges = day4::map_to_ranges(lines);

    auto a_runtime = measure_average_runtime([&ranges]{
            day4::num_of_fully_contained_ranges(ranges);
        }, n_runs).count();
    fmt::print("Average runtime performance num_of_fully_contained_ranges: {} ms.\n", a_runtime);

    auto b_runtime = measure_average_runtime([&ranges]{
            day4::num_of_overlapping_ranges(ranges);
        }, n_runs).count();
    fmt::print("Average runtime performance num_of_overlapping_ranges: {} ms.\n", b_runtime);
}