#pragma once

#include <util.h>
#include <string>
#include <vector>

namespace aoc2022 {

struct PuzzleReader {
  using Line = std::string;
  using Lines = std::vector<Line>;
  using Matrix2i = std::vector<std::vector<unsigned>>;
  using Pair = std::pair<char, char>;
  using Pairs = std::vector<Pair>;
  using Stream = std::istream&;

  virtual ~PuzzleReader() = default;

  virtual auto ReadLine() -> Line = 0;
  virtual auto ReadLines() -> Lines = 0;
  virtual auto ReadMatrix2i() -> Matrix2i = 0;
  virtual auto ReadPairs() -> Pairs = 0;
  virtual auto ReadStream() -> Stream = 0;
};

}  // namespace aoc2022
