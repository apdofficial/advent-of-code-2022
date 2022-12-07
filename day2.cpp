#include <iostream>
#include <fstream>
#include <numeric>

using namespace std;
string const FILE_NAME = "day2.txt";

int main() {

    ifstream dataFile(FILE_NAME);

    if(dataFile.is_open()) {
        cout << "opened " << FILE_NAME << endl;

        dataFile.close();
    }else cout << "unable to open "<< FILE_NAME << endl;


    return 0;
}