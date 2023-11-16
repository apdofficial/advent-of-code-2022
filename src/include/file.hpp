#pragma once

#include <fstream>

#include "string_view"
#include "vector"

namespace aoc
{
    class File
    {
    public:
        // class uses RAII
        // class invariant: file.is_open()
        explicit File(std::string_view file_path);

        ~File();

        auto is_valid() -> bool;

        auto read_lines() -> std::vector<std::string>;

        auto read_pairs() -> std::vector<std::pair<char, char>>;

        auto istream() -> std::istream&;

    private:
        std::ifstream file_;
    };
}