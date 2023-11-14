#pragma once

#include <charconv>
#include <cstdlib>
#include <span>
#include <optional>
#include <string>
#include <ranges>

#include "IDayLineObserver.h"
#include "DayPayload.h"
#include "Day.h"

#include "sort.h"

    auto top_3_elf_calories(std::span<std::optional<int>> calories) -> std::optional<int>;
}

