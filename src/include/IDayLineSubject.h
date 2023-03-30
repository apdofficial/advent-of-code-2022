#pragma once

#include "span"
#include "string"

namespace aoc
{
    class IDayLineSubject
    {
        virtual ~IDayLineSubject() = default;

        virtual void
        update(std::span<const std::string> line) = 0; // let's just assume we only support int type for now
    };
}
