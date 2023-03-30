#pragma once

#include <string_view>
#include <list>

#include "ISubject.h"
#include "IDayProvider.h"

namespace aoc
{
    class DayLineSubject : public ISubject
    {
    public:
        // dependency injection
        explicit DayLineSubject(IDayProviderPtr dayProvider);

        void attach(IDayLineObserverPtr observer) override;

        void detach(IDayLineObserverPtr observer) override;

        void process_day();

    private:
        void update_observers(std::string_view line);

        std::list<IDayLineObserverPtr> day_line_observers_;
        IDayProviderPtr dayProvider_;
    };
}
