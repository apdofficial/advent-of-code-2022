#pragma once

#include <optional>

#include "DayPayload.h"

namespace aoc{
    template<class T>
    class Day: public IDayLineObserver{
    public:
        void on_new(std::string_view line) override = 0;

        void on_lines_completed() override = 0;

        std::optional<T> get_answer_1() {
            return dayPayload.answer1;
        }
        std::optional<T> get_answer_2() {
            return dayPayload.answer2;
        }
    protected:
        DayPayload<T> dayPayload;
    };
}

