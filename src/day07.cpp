#include <day07.hpp>

#include <numeric>
#include <util.h>

#include <sstream>

auto aoc2022::day07::parse_command(std::string_view cmd) -> Command {
    if (cmd.starts_with("$ cd")) return Command::cd;
    if (cmd.starts_with("$ ls")) return Command::ls;
    return Command::not_a_command;
}

auto aoc2022::day07::find_smallest_sufficient(std::vector<unsigned int> &sums, unsigned threshold) -> unsigned {
    std::sort(sums.begin(), sums.end());
    auto sum_iter = std::find_if(sums.begin(), sums.end(), [&threshold](auto sum){
        return sum >= threshold;
    });
    if (sum_iter == sums.end()) return *sums.rbegin();
    return *sum_iter;
}

auto aoc2022::day07::sum_if(std::vector<unsigned int> &sums, unsigned threshold) -> unsigned {
    return std::accumulate(sums.begin(), sums.end(), 0u, [&threshold](auto acc, auto sum){
        if (sum <= threshold) return acc + sum;
        else return acc;
    });
}

auto aoc2022::day07::Directory::add(Directory &&dir) -> std::shared_ptr<Directory> {
    auto name = dir.name();
    auto [iter, added] = entries_.emplace(name, std::make_shared<Directory>(std::move(dir)));
    return std::get<std::shared_ptr<Directory>>(iter->second);
}

auto aoc2022::day07::Directory::add(File &&file) -> std::shared_ptr<File> {
    auto name = file.name();
    auto [iter, added] = entries_.emplace(name, std::make_shared<File>(std::move(file)));
    return std::get<std::shared_ptr<File>>(iter->second);
}

auto aoc2022::day07::Directory::size() const -> unsigned {
    return std::accumulate(entries_.begin(), entries_.end(), std::size_t{0}, [](std::size_t acc, auto &entry) {
        if (std::holds_alternative<std::shared_ptr<File>>(entry.second)) {
            return acc + std::get<std::shared_ptr<File>>(entry.second)->size();
        } else {
            return acc + std::get<std::shared_ptr<Directory>>(entry.second)->size();
        }
    });
}

auto aoc2022::day07::Directory::parent() -> std::shared_ptr<Directory> {
    return parent_;
}

auto aoc2022::day07::Directory::get_subdirectory(const std::string &title) -> std::optional<std::shared_ptr<Directory>> {
    if (!entries_.contains(title)) return std::nullopt;
    auto item = entries_.at(title);
    if (std::holds_alternative<std::shared_ptr<Directory>>(item)) {
        return std::get<std::shared_ptr<Directory>>(item);
    } else {
        return std::nullopt;
    }
}

auto aoc2022::day07::Directory::get_file(const std::string &title) -> std::optional<std::shared_ptr<File>> {
    if (!entries_.contains(title)) return std::nullopt;
    auto item = entries_.at(title);
    if (std::holds_alternative<std::shared_ptr<File>>(item)) {
        return std::get<std::shared_ptr<File>>(item);
    } else {
        return std::nullopt;
    }
}

aoc2022::day07::Directory::Directory(std::shared_ptr<Directory> parent, const std::string &name):
    TreeObject(0, name), parent_(parent), entries_{} {}

auto aoc2022::day07::Directory::add(std::shared_ptr<Directory> parent, std::istream &is) -> void{
    std::string token, name;
    is >> token >> name;
    if (token == "dir" ) {
        add(std::move(Directory(parent, name)));
    } else {
        auto size = map_to_int(token);
        if (size.has_value()) add(std::move(File(size.value(), name)));
    }
}

auto aoc2022::day07::Directory::get_subdirectories() const -> std::vector<std::shared_ptr<Directory>> {
    std::vector<std::shared_ptr<Directory>> subdirs{};
    for(auto& entry: entries_){
        if(std::holds_alternative<std::shared_ptr<Directory>>(entry.second)) {
            auto subdir = std::get<std::shared_ptr<Directory>>(entry.second);
            subdirs.emplace_back(subdir);
        }
    }
    return subdirs;
}

/**
 * @brief Recursively calculate the sizes of all subdirectories.
 * @param dir The directory to calculate the sizes for.
 * @param sums The vector to store the sizes in.
 */
static void calculate_sums(const std::shared_ptr<aoc2022::day07::Directory>& dir, std::vector<unsigned>& sums){
    for (auto& subdir: dir->get_subdirectories()){
        sums.emplace_back(subdir->size());
        calculate_sums(subdir, sums);
    }
}

auto aoc2022::day07::Directory::get_recursive_subdirectory_sizes() const -> std::vector<unsigned> {
    std::vector<unsigned> sums;
    for (auto& subdir: get_subdirectories()){
        sums.emplace_back(subdir->size());
        calculate_sums(subdir, sums);
    }
    return sums;
}

auto aoc2022::day07::process_command_line(const std::string &line, DirectoryTree &tree) -> void {
    std::istringstream line_is{line};
    auto cmd = parse_command(line);
    if (cmd == Command::cd) {
        std::string tag, c, dir;
        line_is >> tag >> c >> dir;
        tree.cd(dir);
        return;
    }
    if (cmd == Command::ls) {
        return;
    }
    tree.current()->add(tree.current(), line_is);
}

auto aoc2022::day07::DirectoryTree::cd(const std::string &dir) -> void {
    if (dir == "/") {
        current_ = root_;
        return;
    }
    if (dir == ".." && current_ == root_) {
        return;
    } else if (dir == ".."){
        current_ = current_->parent();
        return;
    }
    auto subdir = current_->get_subdirectory(dir);
    if (subdir.has_value()) current_ = subdir.value();
}

auto aoc2022::day07::DirectoryTree::current() -> std::shared_ptr<Directory> {
    return current_;
}

auto aoc2022::day07::DirectoryTree::root() -> std::shared_ptr<Directory> {
    return root_;
}

aoc2022::day07::DirectoryTree::DirectoryTree(const Directory &root): root_(std::make_shared<Directory>(root)) {
    current_ = root_;
}
