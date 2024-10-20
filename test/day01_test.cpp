#include <catch2/catch_all.hpp>

#include <util.h>
#include <day01.hpp>
#include <file_puzzle_reader.hpp>

std::vector<std::string> const kShortInput{
    "1000", "2000", "3000", "",     "4000", "", "5000",
    "6000", "",     "7000", "8000", "9000", "", "10000"};

constexpr std::string_view kDataPath = "../../data/day01.txt";

TEST_CASE("Day 01, part 1 test") {
  aoc2022::Day1 day1{kShortInput};
  REQUIRE(day1.SolvePart1() == 24000);
}

TEST_CASE("Day 01, part 2 test") {
  aoc2022::Day1 day1{kShortInput};
  REQUIRE(day1.SolvePart2() == 45000);
}

TEST_CASE("Day 01, file") {
  aoc2022::FilePuzzleReader file(kDataPath);
  aoc2022::Day1 day1{file};
  REQUIRE(day1.SolvePart1() == 69693);
  REQUIRE(day1.SolvePart2() == 200945);
}
