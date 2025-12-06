#include <fstream>
#include <iostream>
#include <memory>
#include <print>
#include <regex>
#include <string>
#include <vector>

using namespace std;

class Problem {
   public:
    Problem(vector<int64_t>& numbers, char op) : numbers(numbers), op(op) {}
    explicit Problem(char op) : op(op) {}

    vector<int64_t> numbers;
    char op;

    int64_t calculate_p1() const {
        int64_t res = op == '+' ? 0 : 1;
        for (int64_t n : numbers) {
            op == '+' ? res += n : res *= n;
        }
        return res;
    }

    int64_t calculate_p2() const {
        int64_t res = op == '+' ? 0 : 1;
        for (int64_t n : numbers) {
        }
        return 0;
    }
};

int main() {
    const string INPUT_FILE = "input/06-example.txt";

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

    int64_t res1 = 0;
    int64_t res2 = 0;

    regex re(R"( )");
    string first_line = lines.front();

    sregex_token_iterator it(first_line.begin(), first_line.end(), re, -1);
    sregex_token_iterator end;

    size_t col = 0;
    for (; it != end; ++it) {
        if (it->str().empty()) {
            continue;
        }
        col++;
    }

    vector<unique_ptr<Problem>> problems;

    string last_line = lines.back();

    lines.resize(lines.size() - 1);

    sregex_token_iterator it1(last_line.begin(), last_line.end(), re, -1);
    sregex_token_iterator end1;

    for (; it1 != end1; ++it1) {
        if (it1->str().empty()) {
            continue;
        }
        problems.push_back(make_unique<Problem>(it1->str()[0]));
    }

    for (size_t i = 0; i < col; i++) {
        vector<int64_t> numbers;
        for (const string& l : lines) {
            sregex_token_iterator it2(l.begin(), l.end(), re, -1);
            sregex_token_iterator end2;

            size_t col_counter = 0;
            for (; it2 != end2; ++it2) {
                if (it2->str().empty()) {
                    continue;
                }

                if (col_counter == i) {
                    numbers.push_back(stol(it2->str()));
                    break;
                }

                col_counter++;
            }
        }
        problems[i]->numbers = numbers;
    }

    for (const auto& p : problems) {
        res1 += p->calculate_p1();
    }

    for (const auto& p : problems) {
        res2 += p->calculate_p2();
    }

    print("Result1: {}", res1);
    print("\nResult2: {}", res2);

    return 0;
}
