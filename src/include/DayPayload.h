#pragma once

#include <vector>
#include <optional>
#include <string>

namespace aoc
{
    template<class T>
    struct DayPayload
    {
        std::vector <std::string> lines {};
        std::optional <T> answer1 = std::nullopt;
        std::optional <T> answer2 = std::nullopt;
    };
};