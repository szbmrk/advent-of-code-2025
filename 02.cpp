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

    for (const auto& id_range : data) {
        auto dash_pos = id_range.find('-');
        int64_t start = stol(id_range.substr(0, dash_pos));
        int64_t end = stol(id_range.substr(dash_pos + 1));

        auto possible_ids = get_possible_ids(start, end);

        for (const auto id : possible_ids) {
            string str = to_string(id);
            auto half = str.size() / 2;
            if (str.substr(0, half) == str.substr(half)) {
                res1 += id;
            }
        }

        for (const auto id : possible_ids) {
            string str = to_string(id);

            auto sequence_length = str.size() / 2;
            while (sequence_length != 0) {
                if (str.size() % sequence_length != 0) {
                    sequence_length--;
                    continue;
                }

                vector<string> splitted_parts;
                for (size_t i = 0; i < str.size(); i += sequence_length) {
                    splitted_parts.push_back(str.substr(i, sequence_length));
                }

                bool match = true;
                for (size_t i = 1; i < splitted_parts.size(); i++) {
                    if (splitted_parts[i - 1] != splitted_parts[i]) {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    res2 += id;
                    break;
                }

                sequence_length--;
            }
        }
    }

    print("Result1: {}", res1);
    print("\nResult2: {}", res2);

    return 0;
}
