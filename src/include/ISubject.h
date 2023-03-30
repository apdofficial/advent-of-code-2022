#pragma once

#include "IDayLineObserver.h"

namespace aoc
{
    class ISubject
    {
    public:
        virtual ~ISubject() = default;

        virtual void attach(IDayLineObserverPtr observer) = 0;

        virtual void detach(IDayLineObserverPtr observer) = 0;
    };
}