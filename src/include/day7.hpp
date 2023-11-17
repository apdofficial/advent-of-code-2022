#pragma once

#include <istream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <span>
#include <optional>
#include <queue>
#include <algorithm>
#include <variant>
#include <memory>
#include <unordered_map>
#include <numeric>
#include <utility>

#include "util.h"

namespace aoc::day7 {
    enum Command {
        cd, ls, not_a_command
    };

    auto parse_command(std::string_view cmd) -> Command;

    /**
     * @brief Finds the smallest sufficient number of elements in sums that sum up to threshold.
     * @param sums The vector of sums to search in.
     * @param threshold The threshold to search for.
     * @return The smallest number of elements in sums that sum up to threshold.
     */
    auto find_smallest_sufficient(std::vector<unsigned int> &sums, unsigned threshold) -> unsigned;

    /**
     * @brief Sums all elements in sums that are less than or equal to threshold.
     * @param sums The vector of sums to search in.
     * @param threshold The threshold to search for.
     * @return The sum of all elements in sums that are less than or equal to threshold.
     */
    auto sum_if(std::vector<unsigned int> &sums, unsigned threshold) -> unsigned;

    struct TreeObject{
    public:
        [[nodiscard]] virtual auto size() const -> unsigned = 0;
        [[nodiscard]] auto name() const -> auto { return name_; }
    protected:
        TreeObject(unsigned size, std::string name): name_(std::move(name)), size_(size) {};
        std::string name_;
        unsigned size_;
    };

    struct File: public TreeObject {
        File(std::size_t size, const std::string& name): TreeObject(size, name) {};

        [[nodiscard]] auto size() const -> unsigned override { return size_; }
    };

    struct Directory: public TreeObject {
        explicit Directory(std::shared_ptr<Directory> parent, const std::string& name);

        auto size() const -> unsigned override;

        auto add(Directory &&dir) -> std::shared_ptr<Directory>;

        auto add(File &&file) -> std::shared_ptr<File>;

        auto add(std::shared_ptr<Directory> parent, std::istream &is) -> void;

        auto get_recursive_subdirectory_sizes() const -> std::vector<unsigned>;

        auto get_subdirectories() const -> std::vector<std::shared_ptr<Directory>>;

        auto get_subdirectory(const std::string &title) -> std::optional<std::shared_ptr<Directory>>;

        auto get_file(const std::string &title) -> std::optional<std::shared_ptr<File>>;

        [[nodiscard]] auto parent() -> std::shared_ptr<Directory>;
    private:
        std::shared_ptr<Directory> parent_;
        std::unordered_map<std::string, std::variant<std::shared_ptr<File>, std::shared_ptr<Directory>>> entries_;
    };

    struct DirectoryTree{
        explicit DirectoryTree(const Directory& root);

        auto cd(const std::string& dir) -> void;

        [[nodiscard]] auto current() -> std::shared_ptr<Directory>;

        [[nodiscard]] auto root() -> std::shared_ptr<Directory>;
    private:
        std::shared_ptr<Directory> root_;
        std::shared_ptr<Directory> current_;
    };

    auto process_command_line(const std::string& line, DirectoryTree &tree) -> void;
}