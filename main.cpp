#include <day01.hpp>

#include <boost/program_options.hpp>

#include <fmt/format.h>
#include <file_puzzle_reader.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace po = boost::program_options;

std::pair<int, int> SolveDay(unsigned day, std::string_view file_path) {
  aoc2022::FilePuzzleReader reader{file_path};
  switch (day) {
    case 1:
      aoc2022::Day1 day{reader};
      return {day.SolvePart1(), day.SolvePart2()};
  }
  throw std::invalid_argument(std::format("Unsupported day {}", day));
}

int main(int ac, char* av[]) {
  try {
    po::options_description desc("aoc2022");
    desc.add_options()("help,h", "produce help message");
    desc.add_options()("version,v", "print the version number");
    desc.add_options()("day,d", po::value<unsigned>(), "day to solve {1...30}");
    desc.add_options()("file,f", po::value<std::string>(), "puzzle file");
    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);
    if (vm.count("help")) {
      desc.print(std::cout);
      return 0;
    }
    if (vm.count("version")) {
      fmt::println("v1.0.0");
      return 0;
    }
    if (!vm.count("day")) {
      fmt::println(stderr,
                   "Error: No day has been provided. Use --help for help.");
      return 1;
    }
    if (!vm.count("file")) {
      fmt::println(
          stderr,
          "Error: No input file has been provided. Use --help for help.");
      return 1;
    }

    auto const day{vm["day"].as<unsigned>()};
    auto const file_path{vm["file"].as<std::string>()};
    fmt::println("Day: {:02}\n", day);

    auto [solution1, solution2] = SolveDay(day, file_path);
    fmt::println("Puzzle 1: {:>20}", solution1);
    fmt::println("Puzzle 2: {:>20}", solution2);

  } catch (std::exception& e) {
    fmt::println(stderr, "Error: {}", e.what());
    return 1;
  }
  return 0;
}
