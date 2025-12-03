#include <fstream>
#include <iostream>
#include <print>
#include <string>
#include <vector>

using namespace std;

namespace {

size_t index_of_largest_num(const string& bank) {
    int largest = static_cast<int>(bank[0]);
    size_t largest_index = 0;

    for (size_t i = 1; i < bank.size(); i++) {
        int current = static_cast<int>(bank[i]);
        if (current > largest) {
            largest = current;
            largest_index = i;
        }
    }

    return largest_index;
}

}  // namespace

int main() {
    const string INPUT_FILE = "input/03-example.txt";

    ifstream file(INPUT_FILE);
    string line;
    vector<string> lines;

    if (!file.is_open()) {
        cerr << "Could not open file\n";
        return 1;
    }

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    int res1 = 0;
    int res2 = 0;

    for (const auto& l : lines) {
        auto largest_index = index_of_largest_num(l);
        print("{} : {}\n", l, largest_index);
    }

    print("Result1: {}", res1);
    print("\nResult2: {}", res2);

    return 0;
}
