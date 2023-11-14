#pragma once

#include "util.h"
#include "sort.h"

#include "DayPayload.h"
#include "File.h"

    auto stooi(std::span<const std::string> lines) -> std::vector<std::optional<int>>;

    class File
    {
    public:
        // class uses RAII
        // class invariant is: file.is_open()
        explicit File(std::string_view file_path);

#include "Day1.hpp"

        auto is_valid() -> bool;

        auto read_lines() -> std::vector<std::string>;

    private:
        std::ifstream file;
    };
}