#include <functional>
#include <chrono>
#include "util.h"

auto aoc::map_to_int(std::string_view line) -> std::optional<int> {
    if (line.empty()) return std::nullopt;
    int result{};
    auto [ptr, ec] = std::from_chars(line.data(), line.data() + line.size(), result);
    if (ec == std::errc()) return result;

    if (ec == std::errc::invalid_argument)
        std::cerr << line << " isn't a number.\n";
    else if (ec == std::errc::result_out_of_range)
        std::cerr << line << " number is larger than an int.\n";

    return std::nullopt;
}

auto aoc::map_to_int(char c) -> std::optional<int> {
    if(c < '0' || c > '9') {
        std::cerr << " isn't a number.\n";
        return std::nullopt;
    }
    return c - '0';
}

auto aoc::map_to_ints(std::span<std::string> lines) -> std::vector<std::optional<int>> {
    std::vector<std::optional<int>> result{};
    std::transform(lines.begin(), lines.end(), std::back_inserter(result), [](const auto &line) {
        return map_to_int(line);
    });
    return result;
}