#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input/01.txt";

int main() {
    ifstream file(INPUT_FILE);
    string line;
    vector<string> lines;

    int dial = 50;
    int password = 0;

    if (!file.is_open()) {
        cerr << "Could not open file.\n";
        return 1;
    }

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    for (const auto& l : lines) {
        cout << "Step: " << l.substr(0, 1) << l.substr(1) << " ";

        int dir = l.starts_with('L') ? -1 : 1;
        int amount = stoi(l.substr(1));

        for (int i = 0; i < amount; i++) {
            dial += 1 * dir;

            if (dial > 99) {
                dial = 0;
            }

            if (dial < 0) {
                dial = 99;
            }

            if (dial == 0) {
                password++;
            }
        }

        // int extra = dial == 0 ? 0 : 1;
        // if (dir == -1 && amount > dial) {
        //     password += (amount - dial) / 100 + extra;
        // }
        //
        // if (dir == 1 && amount > 100 - dial) {
        //     password += (amount + dial) / 100;
        // }
        //
        // dial += amount * dir;
        //
        // dial %= 100;
        //
        // if (dial < 0) {
        //     dial = 100 + dial;
        // }
        //
        // if (dial == 0) {
        //     password++;
        // }

        cout << "Dial: " << dial << "\n";
    }

    cout << "Password: " << password;

    return 0;
}
