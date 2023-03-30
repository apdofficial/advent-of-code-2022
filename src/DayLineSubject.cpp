//
// Created by Andrej Pistek on 28/03/2023.
//

#include "DayLineSubject.h"

#include <utility>

aoc::DayLineSubject::DayLineSubject(IDayProviderPtr dayProvider) :
        dayProvider_{std::move(dayProvider)}
{

}

void aoc::DayLineSubject::attach(IDayLineObserverPtr observer)
{
    day_line_observers_.push_back(observer);
}

void aoc::DayLineSubject::detach(IDayLineObserverPtr observer)
{
    day_line_observers_.remove(observer);
}

void aoc::DayLineSubject::process_day()
{
    auto day = dayProvider_->provide_day();
    if (!day.has_value()) return;
    for (const auto &line: day.value().lines) {
        update_observers(line);
    }
}

void aoc::DayLineSubject::update_observers(std::string_view line)
{
    for (const auto &observer: day_line_observers_) {
        observer->on_new(line);
    }
}