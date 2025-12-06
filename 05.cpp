#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <print>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
using range_t = tuple<int64_t, int64_t>;

namespace {

vector<range_t> merge_ranges(range_t range1, range_t range2) {
    vector<range_t> res;

    auto [start1, end1] = range1;
    auto [start2, end2] = range2;

    if (start1 == start2 && end1 == end2) {
        res.push_back(range1);
        return res;
    }

    if (end1 < start2 || end2 < start1) {
        res.push_back(range1);
        res.push_back(range2);
        return res;
    }

    res.emplace_back(min(start1, start2), max(end1, end2));
    return res;
}

}  // namespace

int main() {
    const string INPUT_FILE = "input/05.txt";

    ifstream file(INPUT_FILE);
    string line;
    vector<string> ranges;
    vector<string> ingredients;

    if (!file.is_open()) {
        cerr << "Could not open file\n";
        return 1;
    }

    bool reading_ranges = true;
    while (getline(file, line)) {
        if (line.empty()) {
            reading_ranges = false;
            continue;
        }

        reading_ranges ? ranges.push_back(line) : ingredients.push_back(line);
    }

    file.close();

    int64_t res1 = 0;
    size_t res2 = 0;

    // 1. part
    for (const string& ingredient : ingredients) {
        for (const string& range : ranges) {
            auto dash_pos = range.find('-');
            int64_t start = stol(range.substr(0, dash_pos));
            int64_t end = stol(range.substr(dash_pos + 1));

            int64_t val = stol(ingredient);

            if (val >= start && val <= end) {
                res1++;
                break;
            }
        }
    }

    // 2. part
    vector<range_t> id_ranges;

    for (const string& range : ranges) {
        auto dash_pos = range.find('-');
        int64_t start = stol(range.substr(0, dash_pos));
        int64_t end = stol(range.substr(dash_pos + 1));

        id_ranges.emplace_back(start, end);
    }

    ranges::sort(id_ranges,
                 [](auto& a, auto& b) { return get<0>(a) < get<0>(b); });

    vector<range_t> merged;
    merged.push_back(id_ranges[0]);

    for (size_t i = 1; i < id_ranges.size(); i++) {
        auto last = merged.back();
        auto current = id_ranges[i];

        auto merged_res = merge_ranges(last, current);

        if (merged_res.size() == 1) {
            merged.back() = merged_res[0];
        } else {
            merged.push_back(current);
        }
    }

    for (auto [start, end] : merged) {
        res2 += end - start + 1;
    }

    print("Result1: {}", res1);
    print("\nResult2: {}", res2);

    return 0;
}
