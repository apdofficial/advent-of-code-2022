#pragma once

#include "IDayProvider.h"
#include "DayPayload.h"

namespace aoc
{

    class NetworkDayProvider : public IDayProvider
    {
        NetworkDayProvider();

        std::optional<DayPayload<int>> provide_day() override;
    };
}