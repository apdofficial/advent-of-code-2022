#include <iomanip>
#include <numeric>

#include "day2.hpp"

std::string const DAY_NR = "2";

// Asymptotic analysis
// complexity is linear O(n)
// no redundant computation
int calculate_strategy_score(const std::vector<std::pair<char, char>> &rounds) {
    return std::accumulate(rounds.begin(), rounds.end(), 0, [](const int accumulator, const auto &pair) -> int {
        // 1 == rock, 2 == paper, 3 == scissors
        const int opponent = pair.first - 'A' + 1;
        const int me = pair.second - 'X' + 1;

        if (opponent == me) {
            return accumulator + me + 3; // draw
        } else if ((me - opponent + 3) % 3 == 1) {
            // win means one of the following
            // ((1 - 3 == -2| +3) == 1 | %3) == 1
            // ((2 - 1 ==  1| +3) == 4 | %3) == 1
            // ((3 - 2 ==  1| +3) == 4 | %3) == 1
            return accumulator + me + 6; // win
        } else {
            return accumulator + me; // lose
        }
    });
}

// Asymptotic analysis
// complexity is linear O(n)
// no redundant computation
int calculate_new_strategy_score(const std::vector<std::pair<char, char>> &rounds) {
    return std::accumulate(rounds.begin(), rounds.end(), 0, [](int accumulator, auto &pair) -> int {
        // 1 == rock, 2 == paper, 3 == scissors
        int opponent = pair.first - 'A' + 1;
        // 1 == X == lose, 2 == Y == draw, 3 == Z == win
        int me = pair.second - 'X' + 1;

        if (me == 1) { // lose
            if (opponent == 1) {
                return accumulator + 3;
            } else if (opponent == 2) {
                return accumulator + 1;
            } else return accumulator + 2;
        } else if (me == 2) { // draw
            return accumulator + opponent + 3;
        } else { //win
            if (opponent == 1) {
                return accumulator + 2 + 6;
            } else if (opponent == 2) {
                return accumulator + 3 + 6;
            } else return accumulator + 1 + 6;
        }
    });
}

void run_day_2() {
    std::string const fileName = "day" + DAY_NR + ".txt";
    std::cout << "--Day " << DAY_NR << " START--" << std::endl;
    std::vector<std::pair<char, char>> rounds;
    std::fstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(fileName) << "\n";
        return;
    }

    std::pair<char, char> currentRound;
    while (file >> currentRound.first >> currentRound.second) {
        rounds.push_back(currentRound);
    }
    std::cout << "calculate_strategy_score:     " << calculate_strategy_score(rounds) << "\n";
    std::cout << "calculate_new_strategy_score: " << calculate_new_strategy_score(rounds) << "\n";
    std::cout << "--Day " << DAY_NR << " END--\n" << std::endl;
}