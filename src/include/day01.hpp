#pragma once

#include <day.h>
#include <puzzle_reader.hpp>
#include <string>
#include <vector>

namespace aoc2022 {

struct Day1 : public IDay {
  Day1(PuzzleReader&);
  Day1(std::vector<std::string> const&);

  [[nodiscard]] auto SolvePart1() -> int override;
  [[nodiscard]] auto SolvePart2() -> int override;

 private:
  PuzzleReader::Lines lines_;
};

}  // namespace aoc2022
