#pragma once

#include <optional>
#include <vector>

#include "IDayProvider.h"
#include "DayPayload.h"
#include "File.h"

namespace aoc
{
    class FileDayProvider : public IDayProvider
    {
    public:
        explicit FileDayProvider(std::string_view file_path);

        auto provide_day() -> std::optional<DayPayload<int>> override;
    private:
        File file;
    };
}
