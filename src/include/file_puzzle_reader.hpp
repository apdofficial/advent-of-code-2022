#pragma once

#include <util.h>
#include <fstream>
#include <puzzle_reader.hpp>
#include <string_view>

namespace aoc2022 {

struct FilePuzzleReader : public PuzzleReader {
  FilePuzzleReader(std::string_view file_path);

  ~FilePuzzleReader() override;

  FilePuzzleReader() = delete;

  FilePuzzleReader(FilePuzzleReader const&) = delete;
  FilePuzzleReader(FilePuzzleReader&&) = delete;

  FilePuzzleReader operator=(FilePuzzleReader const&) = delete;
  FilePuzzleReader operator=(FilePuzzleReader&&) = delete;

  auto ReadLine() -> Line override;

  auto ReadLines() -> Lines override;

  auto ReadMatrix2i() -> Matrix2i override;

  auto ReadPairs() -> Pairs override;

  auto ReadStream() -> Stream override;

 private:
  std::ifstream file_{};
};

}  // namespace aoc2022
