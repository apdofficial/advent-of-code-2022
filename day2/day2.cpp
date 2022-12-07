#include "day2.h"


std::string const FILE_NAME = "day2.txt";

int follow_choice(const std::vector<std::pair<char,char>>& record) {
    auto scoreTransformer = [](int accumulator, auto& pair) -> int {
        // Transform both inputs numbers:
        // 0 == rock, 1 == paper, 2 == scissors
        int oponent = pair.first-'A';
        int me = pair.second-'X';

        // Score for the choice:
        // Rock == 1, Paper == 2, Scissors == 3
        int score = me + 1;

        // Score for the result:
        if (oponent == me) return accumulator + score + 3; // draw
        // Winining choice has a rank one higher than the oposing choice
        // the only wrinkle is Rock beating Scissors which is why we need modulo.
        if ((me - oponent + 3) % 3 == 1) return accumulator + score + 6;
        return accumulator + score; // lose
    };
    return std::accumulate(record.begin(), record.end(), 0, scoreTransformer);
}

int runDay2(){
    std::vector<std::pair<char,char>> rounds;
    std::fstream file(FILE_NAME);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(FILE_NAME) << "\n";
        return 1;
    }

    std::pair<char,char> currentRound;
    while (file >> currentRound.first >> currentRound.second) {
//        std::cout << currentRound.first << " " << currentRound.second << std::endl;
        rounds.push_back(currentRound);
    }
    std::cout << "The total score while following the strategy guide is " << follow_choice(rounds) << "\n";
}