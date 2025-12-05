#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

void readFile(vector<pair<long long, long long>>& data, vector<long long>& values) {

    ifstream myFile("data.txt");

    if (myFile.is_open()) {
        string line;
        bool readingRanges = true;


            while (getline(myFile, line)) {

                // blank line separates sections
                if (line.empty()) {
                    readingRanges = false;
                    continue;
                }

                if (readingRanges) {
                    int pos = line.find('-');
                    long long a = stoll(line.substr(0, pos));
                    long long b = stoll(line.substr(pos + 1));
                    data.emplace_back(a, b);
                }
                else {
                    values.push_back(stoll(line));
                }
            }

        myFile.close();
    }
}

void Part1Solution(vector<pair<long long, long long>>& ranges, vector<long long>& ids) {

    sort(ranges.begin(), ranges.end());
    sort(ids.begin(), ids.end());

    int count = 0;
    for (long long id : ids) {

        for (auto [l, r] : ranges) {

            if (id >= l && id <= r) {
                count++;
                break;
            }
            else if (id < l)
                break;
        }
    }

    cout << "Part 1 Solution: " << count << endl;
}

void Part2Solution(vector<pair<long long, long long>>& ranges) {

    sort(ranges.begin(), ranges.end());

    long long count = 0;
    auto [currentL, currentR] = ranges[0];

    for (int i = 1; i < ranges.size(); i++) {

        long long l = ranges[i].first;
        long long r = ranges[i].second;

        if (l <= currentR + 1) {
            if (r > currentR)
                currentR = r;
        }
        else {
            count += (currentR - currentL + 1);
            currentL = l;
            currentR = r;
        }

    }

    count += currentR - currentL + 1;

    cout << "Part 2 Solution: " << count << endl;

}

int main() {

    vector<pair<long long, long long>> data;
    vector<long long> values;
    readFile(data, values);

    Part1Solution(data, values);
    Part2Solution(data);
}
