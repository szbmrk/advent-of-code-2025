#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <print>
#include <string>
#include <vector>

using namespace std;

int main() {
    const string INPUT_FILE = "input/07.txt";

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

    vector<size_t> cols_of_beam;

    for (size_t i = 0; i < matrix[0].size(); i++) {
        char current = matrix[0][i];

        if (current == 'S') {
            cols_of_beam.push_back(i);
            break;
        }
    }

    print("{}\n", cols_of_beam);
    for (size_t i = 1; i < matrix.size(); i++) {
        for (size_t k = 0; k < cols_of_beam.size();) {
            size_t col = cols_of_beam[k];
            auto current = matrix[i][col];
            if (current == '.') {
                matrix[i][col] = '|';
                continue;
            }

            if (current == '^') {
                if (col < matrix[i].size() - 1) {
                    matrix[i][col + 1] = '|';
                    bool contains = ranges::find(cols_of_beam, col + 1) !=
                                    cols_of_beam.end();
                    if (!contains) {
                        cols_of_beam.push_back(col + 1);
                    }
                }

                if (col > 0) {
                    matrix[i][col - 1] = '|';
                    bool contains = ranges::find(cols_of_beam, col - 1) !=
                                    cols_of_beam.end();
                    if (!contains) {
                        cols_of_beam.push_back(col - 1);
                    }
                }

                cols_of_beam.erase(cols_of_beam.begin() +
                                   static_cast<int64_t>(k));
                continue;
            }
            k++;
        }
    }

    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            char current = matrix[i][j];
            if (current == '^') {
                if (matrix[i - 1][j] == '|') {
                    res1++;
                }
            }
        }
    }

    print("Result1: {}", res1);
    print("\nResult2: {}", res2);

    return 0;
}
