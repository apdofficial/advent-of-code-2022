#pragma once

#include <string_view>
#include <memory>

namespace aoc
{
    class IDayLineObserver
    {
    public:
        IDayLineObserver() = default;
        ~IDayLineObserver() = default;

        virtual void on_new(std::string_view line) = 0;
        virtual void on_lines_completed() = 0;
    };

    using IDayLineObserverPtr = std::shared_ptr<IDayLineObserver>;
}

