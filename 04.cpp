#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <print>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

namespace {

int count_adj(const vector<vector<char>>& matrix,
              size_t col,
              size_t row,
              size_t max_col,
              size_t max_row) {
    const vector<tuple<int8_t, int8_t>> directions = {
        make_tuple(0, 1),  make_tuple(0, -1),  make_tuple(1, 0),
        make_tuple(1, 1),  make_tuple(1, -1),  make_tuple(-1, 0),
        make_tuple(-1, 1), make_tuple(-1, -1),
    };

    int adj = 0;
    for (auto [x_dir, y_dir] : directions) {
        size_t x = col + x_dir;
        size_t y = row + y_dir;

        if (x < 0 || x > max_col) {
            continue;
        }

        if (y < 0 || y > max_row) {
            continue;
        }

        if (matrix[y][x] == '@') {
            adj++;
        }
    }
    return adj;
}

}  // namespace

int main() {
    const string INPUT_FILE = "input/04.txt";

    ifstream file(INPUT_FILE);
    vector<vector<char>> matrix;
    string line;

    if (!file.is_open()) {
        cerr << "Could not open file\n";
        return 1;
    }

    while (getline(file, line)) {
        vector<char> row;
        for (const char c : line) {
            row.push_back(c);
        }
        matrix.push_back(row);
    }

    file.close();

    int res1 = 0;
    int res2 = 0;

    // 1. part
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            auto c = matrix[i][j];
            if (c != '@') {
                continue;
            }

            int adj = count_adj(matrix, j, i, matrix[i].size() - 1,
                                matrix.size() - 1);

            if (adj < 4) {
                res1++;
            }
        }
    }

    // 2. part
    bool changed = true;
    while (changed) {
        changed = false;
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                auto c = matrix[i][j];
                if (c != '@') {
                    continue;
                }

                int adj = count_adj(matrix, j, i, matrix[i].size() - 1,
                                    matrix.size() - 1);

                if (adj < 4) {
                    matrix[i][j] = 'x';
                    res2++;
                    changed = true;
                }
            }
        }
    }

    print("Result1: {}", res1);
    print("\nResult2: {}", res2);

    return 0;
}
