#include <file_puzzle_reader.hpp>
#include <sstream>

namespace aoc2022 {

FilePuzzleReader::FilePuzzleReader(std::string_view file_path)
    : file_(std::ifstream(file_path.data())) {
  if (!file_.is_open()) {
    throw std::runtime_error(
        std::format("Failed to open FilePuzzleReader at path: {}", file_path));
  }
}

FilePuzzleReader::~FilePuzzleReader() {
  file_.close();
}

auto FilePuzzleReader::ReadLine() -> Line {
  std::stringstream buffer;
  buffer << file_.rdbuf();
  return buffer.str();
}

auto FilePuzzleReader::ReadLines() -> Lines {
  Lines lines;
  Line line;
  while (getline(file_, line)) {
    lines.emplace_back(line);
  }
  return lines;
}

auto FilePuzzleReader::ReadMatrix2i() -> Matrix2i {
  Matrix2i matrix;
  Line line;
  int i = 0;
  while (getline(file_, line)) {
    matrix.emplace_back();
    for (char& c : line) {
      matrix[i].emplace_back((int)c - '0');
    }
    ++i;
  }
  return matrix;
}

auto FilePuzzleReader::ReadPairs() -> Pairs {
  Pairs rounds;
  Pair round;
  while (file_ >> round.first >> round.second) {
    rounds.emplace_back(round);
  }
  return rounds;
}

auto FilePuzzleReader::ReadStream() -> Stream {
  return file_;
}

}  // namespace aoc2022
