//
// Created by Andrej Egeniq on 08/12/2022.
//

#include "day3.h"


std::string const DAY_NR = "3";


int run_day_3(){
    std::string const fileName = "day" + DAY_NR + ".txt";
    std::cout << "--Day " << DAY_NR << " START--" << std::endl;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(fileName) << "\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }


    std::cout << "--Day " << DAY_NR << " END--\n" << std::endl;
    return 0;
}