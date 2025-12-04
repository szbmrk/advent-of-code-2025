#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <print>
#include <string>
#include <vector>

using namespace std;

namespace {

size_t index_of_largest(const string& bank, size_t from = 0) {
    int largest = -1;
    size_t largest_index = -1;

    for (size_t i = from; i < bank.size(); i++) {
        int current = bank[i] - '0';

        if (current > largest) {
            largest = current;
            largest_index = i;
        }
    }

    return largest_index;
}

}  // namespace

int main() {
    const string INPUT_FILE = "input/03.txt";

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
    int64_t res2 = 0;

    for (const auto& l : lines) {
        // 1. part
        auto index_of_first = index_of_largest(l.substr(0, l.size() - 1));
        auto index_of_second = index_of_largest(l, index_of_first + 1);

        int first_largest = l[index_of_first] - '0';
        int second_largest = l[index_of_second] - '0';
        int joltage = (first_largest * 10) + second_largest;

        res1 += joltage;

        // 2. part
        string digits;
        auto free_digits = l.size() - 12;
        size_t index_of_first_digit =
            index_of_largest(l.substr(0, free_digits + 1));
        digits += to_string(l[index_of_first_digit] - '0');

        free_digits = free_digits - index_of_first_digit;
        auto prev_index = index_of_first_digit;

        for (size_t i = 1; i < 12; i++) {
            size_t max_index = prev_index + 1 + free_digits;

            auto index =
                index_of_largest(l.substr(0, max_index + 1), prev_index + 1);

            free_digits -= index - prev_index - 1;
            prev_index = index;
            digits += to_string(l[index] - '0');
        }

        res2 += stol(digits);
    }

    print("Result1: {}", res1);
    print("\nResult2: {}", res2);

    return 0;
}
