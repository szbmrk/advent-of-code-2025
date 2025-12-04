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
    const string INPUT_FILE = "input/04-example.txt";

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

    size_t row = 0;
    for (const vector<char>& cell_row : matrix) {
        size_t col = 0;
        for (char c : cell_row) {
            if (c != '@') {
                continue;
            }

            int adj = count_adj(matrix, col, row, cell_row.size() - 1,
                                matrix.size() - 1);

            if (adj < 4) {
                res1++;
            }

            col++;
        }

        row++;
        col = 0;
    }

    print("Result1: {}", res1);
    print("\nResult2: {}", res2);

    return 0;
}
