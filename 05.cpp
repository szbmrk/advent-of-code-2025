#include <fstream>
#include <iostream>
#include <print>
#include <string>
#include <vector>

using namespace std;

int main() {
    const string INPUT_FILE = "input/05-example.txt";

    ifstream file(INPUT_FILE);
    string line;
    vector<string> ranges;
    vector<string> ingredients;

    if (!file.is_open()) {
        cerr << "Could not open file\n";
        return 1;
    }

    bool reading_ranges = true;
    while (getline(file, line)) {
        if (line.empty()) {
            reading_ranges = false;
        }

        reading_ranges ? ranges.push_back(line) : ingredients.push_back(line);
    }

    file.close();

    return 0;
}
