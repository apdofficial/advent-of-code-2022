#include "aoc.hpp"

auto aoc::stooi(std::string_view line) -> std::optional<int>
{
    if (line.empty()) return std::nullopt;
    int result{};
    auto [ptr, ec] {std::from_chars(line.data(), line.data() + line.size(), result)};
    if (ec == std::errc()) return result;

    if (ec == std::errc::invalid_argument)
        std::cout << line << " isn't a number.\n";
    else if (ec == std::errc::result_out_of_range)
        std::cout << line << " number is larger than an int.\n";

    return std::nullopt;
}

auto aoc::stooi(std::span<const std::string> lines) -> std::vector<std::optional<int>>
{
    std::vector<std::optional<int>> result{};
    for (const auto &line: lines) {
        result.push_back(stooi(line));
    }
    return result;
}

auto aoc::File::is_valid() -> bool
{
    return file.is_open();
}

auto aoc::File::read_lines() -> std::vector<std::string>
{
    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

aoc::File::~File()
{
    file.close();
}

aoc::File::File(std::string_view file_path)
{
    file = std::ifstream(file_path.data());
    if (!is_valid())
        throw std::runtime_error("Failed to open file at path: " + std::string(file_path));
}
