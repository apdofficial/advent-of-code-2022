#include <catch2/catch_all.hpp>
#include <fmt/core.h>

#include "day07.hpp"
#include "util.h"
#include "file.hpp"

using namespace aoc2022::day07;

std::vector<std::string> short_command_lines_d7{"$ cd /",
                                                "$ ls",
                                                "dir a",
                                                "14848514 b.txt",
                                                "8504156 c.dat",
                                                "dir d",
                                                "$ cd a",
                                                "$ ls",
                                                "dir e",
                                                "29116 f",
                                                "2557 g",
                                                "62596 h.lst",
                                                "$ cd e",
                                                "$ ls",
                                                "584 i",
                                                "$ cd ..",
                                                "$ cd ..",
                                                "$ cd d",
                                                "$ ls",
                                                "4060174 j",
                                                "8033020 d.log",
                                                "5626152 d.ext",
                                                "7214296 k"};

constexpr std::string_view DATA_PATH = "../../data/day07.txt";


TEST_CASE("Day 07, part 1 test") {
    auto tree = DirectoryTree(Directory(nullptr, "/"));
    for (const auto& cmd_line: short_command_lines_d7){
        process_command_line(cmd_line, tree);
    }
    auto sums = tree.root()->get_recursive_subdirectory_sizes();

    auto a = tree.root()->get_subdirectory("a").value();
    auto d = tree.root()->get_subdirectory("d").value();
    auto e = a->get_subdirectory("e").value();

    REQUIRE(tree.root()->size() == 48381165);
    REQUIRE(d->size() == 24933642);
    REQUIRE(a->size() == 94853);
    REQUIRE(e->size() == 584);

    REQUIRE(sum_if(sums, 100000) == 95437);
}

TEST_CASE("Day 07, part 2 test") {
    auto tree = DirectoryTree(Directory(nullptr, "/"));
    for (const auto& cmd_line: short_command_lines_d7){
        process_command_line(cmd_line, tree);
    }
    auto sums = tree.root()->get_recursive_subdirectory_sizes();
    REQUIRE(find_smallest_sufficient(sums, 30000000) == 24933642);
}

TEST_CASE("Day 07 file (correctness)") {
    constexpr auto total_mem = 70000000;
    constexpr auto required_for_update_mem = 30000000;

    aoc2022::File file(DATA_PATH);
    REQUIRE(file.is_valid());

    auto tree = DirectoryTree(Directory(nullptr, "/"));
    for (const auto& cmd_line: file.read_lines()){
        process_command_line(cmd_line, tree);
    }
    auto sums = tree.root()->get_recursive_subdirectory_sizes();

    auto small_dirs_sum = sum_if(sums, 100000);
    REQUIRE(small_dirs_sum == 1390824);
    fmt::println("small_dirs_sum: {}", small_dirs_sum);

    int used_mem = tree.root()->size();
    auto required_mem = required_for_update_mem - (total_mem - used_mem);
    auto smallest_sufficient = find_smallest_sufficient(sums, required_mem);
    REQUIRE(smallest_sufficient == 7490863);
    fmt::println("smallest_sufficient: {}", smallest_sufficient);
}
