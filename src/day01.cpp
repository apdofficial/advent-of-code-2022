#include <util.h>
#include <algorithm>
#include <day01.hpp>
#include <functional>
#include <numeric>

namespace aoc2022 {

Day1::Day1(PuzzleReader& reader) : lines_(reader.ReadLines()) {}

Day1::Day1(PuzzleReader::Lines const& lines) : lines_(lines) {}

int Day1::SolvePart1() {
  int max = 0;
  int acc = 0;
  for (auto const& line : lines_) {
    try {
      acc += std::stoi(line);
    } catch (std::exception const& ex) {
      if (acc > max) {
        max = acc;
      }
      acc = 0;
    }
  }
  if (acc > max) {
    max = acc;
  }
  return max;
}

int Day1::SolvePart2() {
  std::vector<int> elves{};
  int acc = 0;
  for (auto const& line : lines_) {
    try {
      acc += std::stoi(line);
    } catch (std::exception const& ex) {
      elves.push_back(acc);
      acc = 0;
    }
  }
  if (acc > 0) {
    elves.push_back(acc);
  }
  std::sort(elves.begin(), elves.end());
  return std::accumulate(elves.rbegin(), elves.rbegin() + 3, 0, std::plus<>());
}

}  // namespace aoc2022
