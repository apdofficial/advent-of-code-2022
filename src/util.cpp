#include <util.h>
#include <charconv>
#include <iostream>

auto aoc2022::map_to_int(std::string_view line) -> std::optional<int> {
  if (line.empty())
    return std::nullopt;
  int result{};
  auto [ptr, ec] =
      std::from_chars(line.data(), line.data() + line.size(), result);
  if (ec == std::errc())
    return result;
  return std::nullopt;
}

auto aoc2022::map_to_int(char c) -> std::optional<int> {
  if (c < '0' || c > '9') {
    std::cerr << " isn't a number.\n";
    return std::nullopt;
  }
  return c - '0';
}

auto aoc2022::map_to_ints(std::span<std::string> lines)
    -> std::vector<std::optional<int>> {
  std::vector<std::optional<int>> result{};
  std::ranges::transform(lines, std::back_inserter(result),
                         [](const auto& line) { return map_to_int(line); });
  return result;
}

auto aoc2022::map(std::span<std::string> lines) -> std::vector<int> {
  std::vector<int> result;
  for (auto const& line: lines) {
    auto val{aoc2022::map_to_int(line)};
    if (val.has_value()) {
        result.push_back(val.value());
    }
  }
  return result;
}
