//
// Created by Andrej Pistek on 28/03/2023.
//

#include "File.h"

aoc::File::File(std::string_view file_path)
{
    file_ = std::ifstream(file_path.data());
    if (!is_valid())
        throw std::runtime_error("Failed to open file at path: " + std::string(file_path));
}

aoc::File::~File()
{
    file_.close();
}

auto aoc::File::is_valid() -> bool
{
    return file_.is_open();
}

auto aoc::File::read_lines() -> std::vector<std::string>
{
    std::vector<std::string> lines;
    std::string line;
    while (getline(file_, line)) {
        lines.push_back(line);
    }
    return lines;
}
