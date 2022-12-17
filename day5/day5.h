#ifndef ADVENT_OF_CODE_2022_DAY5_H
#define ADVENT_OF_CODE_2022_DAY5_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>

struct Command {
    uint32_t crateNr;
    size_t from;
    size_t to;

    friend std::istream& operator>>(std::istream& s, Command& o) {
        std::string word;
        s >> word >> o.crateNr >> word >> o.from >> word >> o.to;
        --o.crateNr; // start form 0
        --o.from; // start form 0
        --o.to; // start form 0
        return s;
    }
};

int run_day_5();


#endif //ADVENT_OF_CODE_2022_DAY5_H
