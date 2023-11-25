#pragma once

#include <fstream>
#include <sstream>
#include <string_view>
#include <vector>

#include "util.h"

namespace aoc
{
    class File
    {
    public:
        // class uses RAII
        // class invariant: file.is_open()
        explicit File(std::string_view file_path);

        ~File();

        [[nodiscard]] auto is_valid() const -> bool;

        [[nodiscard]] auto read_string() -> std::string;

        [[nodiscard]] auto read_lines() -> std::vector<std::string>;

        [[nodiscard]] auto read_matrix() -> std::vector<std::vector<unsigned>>;

        [[nodiscard]] auto read_pairs() -> std::vector<std::pair<char, char>>;

        [[nodiscard]] auto istream() -> std::istream&;

    private:
        std::ifstream file_;
    };
}