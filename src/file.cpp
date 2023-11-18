//
// Created by Andrej Pistek on 28/03/2023.
//

#include "file.hpp"


aoc::File::File(std::string_view file_path): file_(std::ifstream(file_path.data()))
{
    if (!is_valid())
        throw std::runtime_error("Failed to open file at path: " + std::string(file_path));
}

aoc::File::~File()
{
    file_.close();
}

auto aoc::File::is_valid() const -> bool
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

auto aoc::File::read_matrix() -> std::vector<std::vector<unsigned>>
{
    std::vector<std::vector<unsigned>> matrix;
    std::string line;
    unsigned i = 0;
    while (getline(file_, line)) {
        matrix.emplace_back();
        for(char& c: line){
            matrix[i].emplace_back((int)c - '0');
        }
        ++i;
    }
    return matrix;
}

auto aoc::File::read_pairs() -> std::vector<std::pair<char, char>>
{
    std::vector<std::pair<char, char>> rounds;
    std::pair<char, char> currentRound;
    while (file_ >> currentRound.first >> currentRound.second) {
        rounds.push_back(currentRound);
    }
    return rounds;
}

auto aoc::File::istream() -> std::istream&{
    return file_;
}
