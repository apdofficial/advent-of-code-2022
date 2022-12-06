#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;
string const FILE_NAME = "calories.txt";

struct Elf {
    int calories = 0;
};

int sum_top_calories(vector<Elf> const& elfs, int nr);

int main() {
    vector<Elf> elfs;

    ifstream dataFile(FILE_NAME);

    if(dataFile.is_open()){
        cout << "opened "<< FILE_NAME << endl;

        string line;
        bool shouldCreateElf = true;

        while (getline(dataFile, line)) {
            if (!line.empty()) {
                try{
                    int caloriesItem = stoi(line);
                    if (shouldCreateElf){
                        elfs.push_back(Elf{.calories = caloriesItem});
                    }else{
                        elfs.back().calories += caloriesItem;
                    }
                }catch (std::invalid_argument& e){
                    cout << "exception:" << e.what() << "for input: " << line << endl;
                }
                shouldCreateElf = false;
            }else{
                shouldCreateElf = true;
            }
        }
        dataFile.close();
    }else cout << "unable to open "<< FILE_NAME << endl;

    sort(elfs.begin(), elfs.end(), [](Elf const& lhs, Elf const& rhs){
        return lhs.calories > rhs.calories;
    });


    int topNr = 3;

    cout << "Result:" << endl;
    cout << "Number of elfs: " << elfs.size() << endl;
    cout << "max calories for single elf: " << elfs.begin()->calories << endl;
    cout << "calories for top " << topNr<< " elfs: " << sum_top_calories(elfs, topNr)<< endl;
    return 0;
}

int sum_top_calories(vector<Elf> const& elfs, int nr){
    auto endIter  = elfs.end();
    if (elfs.size() > nr){
        endIter = elfs.begin() + nr;
    }
    return accumulate(elfs.begin(), endIter, 0, [](int const& accumulator, Elf elf){
        return accumulator + elf.calories;
    });
}