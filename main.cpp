#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
string const FILE_NAME = "calories.txt";

struct Elf {
    int calories = 0;
};

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

    auto maxCaloriesElfIter = max_element(elfs.begin(), elfs.end(), [](Elf const& lhs, Elf const& rhs){
        return lhs.calories < rhs.calories;
    });

    cout << "Result:" << endl;
    cout << "Number of elfs: " << elfs.size() << endl;
    cout << "max calories for single elf: " << maxCaloriesElfIter->calories << endl;

    return 0;
}
