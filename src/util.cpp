#include <functional>
#include <chrono>
#include "util.h"

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

auto aoc::measure_average_runtime(const std::function<void()>& fn, std::size_t n_runs) -> std::chrono::milliseconds {
    using namespace std::chrono;
    milliseconds total_time(0);
    auto start_time = steady_clock::now();
    for (std::size_t i=0; i < n_runs; ++i) {
        fn();
        total_time += duration_cast<milliseconds>(steady_clock::now() - start_time);
    }
    return milliseconds {total_time.count() / n_runs};
}