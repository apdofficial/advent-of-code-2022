#pragma once

#include <optional>
#include <fstream>
#include <memory>

#include "DayPayload.h"

namespace aoc
{
    class IDayProvider
    {
    public:
        virtual ~IDayProvider() = default;

        virtual std::optional<DayPayload<int>> provide_day() = 0; // let's just assume we only support int type for now
    };

    using IDayProviderPtr = std::shared_ptr<IDayProvider>;
}

