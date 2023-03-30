#include <catch2/catch_all.hpp>
#include "aoc.hpp"

std::vector<std::string> short_lines{
        "1000", "2000", "3000", "",
        "4000", "",
        "5000", "6000", "",
        "7000", "8000", "9000", "",
        "10000"
};
std::vector<std::optional<int>> short_calories{aoc::map_to_int(short_lines)};

constexpr std::string_view DATA_PATH = "./data/data1.txt";

using namespace aoc;

TEST_CASE("Day 1, part 1 test")
{
    auto result = Day1<int>::compute_top_1_elf_calories(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 24000);
}

TEST_CASE("Day 1, part 2 test (Quick Sort)")
{
    auto result = Day1<int>::compute_top_3_elf_calories_quick(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 45000);
}

TEST_CASE("Day 1, part 2 test (Bubble Sort)")
{
    auto result = Day1<int>::compute_top_3_elf_calories_bubble(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 45000);
}

TEST_CASE("Day 1, part 2 test (Inplace)")
{
    auto result = Day1<int>::compute_top_3_elf_calories_inplace(short_calories);
    REQUIRE(result.has_value());
    REQUIRE(result.value() == 45000);
}

TEST_CASE("Day 1 test")
{
    auto dayProvider = std::make_shared<FileDayProvider>(DATA_PATH);
    auto dayLineSubject = DayLineSubject(dayProvider);
    auto day1 = std::shared_ptr<Day1<int>>();

    dayLineSubject.attach(day1);
    dayLineSubject.process_day();

    REQUIRE(day1->get_answer_1().has_value());
    REQUIRE(day1->get_answer_1().value() == 24000);

    REQUIRE(day1->get_answer_2().has_value());
    REQUIRE(day1->get_answer_2().value() == 200945);
}