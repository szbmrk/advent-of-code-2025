#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace {

vector<string> split(const string& str, char delimiter) {
    vector<string> res;
    stringstream stream(str);
    string part;

    while (getline(stream, part, delimiter)) {
        res.push_back(part);
    }

    return res;
}

vector<int64_t> get_possible_ids(int64_t start, int64_t end) {
    vector<int64_t> res;

    for (int64_t i = start; i <= end; i++) {
        res.push_back(i);
    }

    return res;
}

}  // namespace

int main() {
    const string INPUT_FILE = "input/02.txt";

    ifstream file(INPUT_FILE);
    string line;

    if (!file.is_open()) {
        cerr << "Could not open file\n";
        return 1;
    }

    getline(file, line);

    file.close();

    vector<string> data = split(line, ',');

    int64_t res1 = 0;
    int64_t res2 = 0;

    for (const auto& idRange : data) {
        auto dashPos = idRange.find('-');
        int64_t start = stol(idRange.substr(0, dashPos));
        int64_t end = stol(idRange.substr(dashPos + 1));

        auto possibleIds = get_possible_ids(start, end);
        for (const auto id : possibleIds) {
            string str = to_string(id);
            auto half = str.size() / 2;
            if (str.substr(0, half) == str.substr(half)) {
                res1 += id;
            }
        }

        for (const auto id : possibleIds) {
            string str = to_string(id);
            bool match = false;
            for (size_t i = 2; i < str.size(); i++) {
                for (size_t j = 0; j < i; j++) {
                }
            }

            if (match) {
                res2 += id;
            }
        }
    }

    print("Result1: {}", res1);
    print("Result2: {}", res2);

    return 0;
}
