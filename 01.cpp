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
    int password1 = 0;
    int password2 = 0;

    if (!file.is_open()) {
        cerr << "Could not open file.\n";
        return 1;
    }

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    // 1. feladat
    for (const auto& l : lines) {
        int dir = l.starts_with('L') ? -1 : 1;
        int amount = stoi(l.substr(1));

        dial += amount * dir;
        dial %= 100;

        if (dial < 0) {
            dial = 100 + dial;
        }

        if (dial == 0) {
            password1++;
        }
    }

    // 2. feladat
    dial = 50;
    for (const auto& l : lines) {
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
                password2++;
            }
        }
    }

    cout << "Password1: " << password1;
    cout << "\nPassword2: " << password2;

    return 0;
}
