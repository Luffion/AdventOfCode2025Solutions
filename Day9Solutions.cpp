#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

void readFile(vector<pair<long long, long long>>& data) {
    ifstream myFile("data.txt");

    if (myFile.is_open()) {
        string line;

        while (getline(myFile, line)) {
            long long pos = line.find(',');

            long long x = stoll(line.substr(0, pos));
            long long y = stoll(line.substr(pos + 1));

            data.emplace_back(x, y);
        }

        myFile.close();
    }
}

void Part1Solution(vector<pair<long long, long long>>& tiles) {

    long long maxArea = 0;

    for (int i = 0; i < tiles.size(); i++) {
        auto [x1, y1] = tiles[i];
        for (int j = i + 1; j < tiles.size(); j++) {
            auto [x2, y2] = tiles[j];
            long long area = (abs(x2 - x1) + 1) * (abs(y2 - y1) + 1);
            maxArea = max(maxArea, area);
        }
    }

    cout << "Part 1 Solution: " << maxArea << endl;
}

void Part2Solution(vector<pair<long long, long long>>& redTiles) {
    
    int n = redTiles.size();

    using Rect = tuple<long long, pair<long long, long long>, pair<long long, long long>>;

    priority_queue<Rect> areas;
    for (int i = 0; i < n; i++) {
        auto [x1, y1] = redTiles[i];
        for (int j = i + 1; j < n; j++) {
            auto [x2, y2] = redTiles[j];
            
            pair<long long, long long> UL = { min(x1,x2), min(y1,y2) };
            pair<long long, long long> LR = { max(x1,x2), max(y1,y2) };

            long long area = (LR.first - UL.first + 1) * (LR.second - UL.second + 1);
            
            areas.push({ area, UL, LR });
        }
    }

    vector<pair<pair<long long, long long>, pair<long long, long long>>> edges;
    for (int i = 0; i < n; i++) {
        auto pt1 = redTiles[i];
        auto pt2 = redTiles[(i + 1) % n];
        auto lA = make_pair(min(pt1.first, pt2.first), min(pt1.second, pt2.second));
        auto lB = make_pair(max(pt1.first, pt2.first), max(pt1.second, pt2.second));
        edges.push_back({ lA, lB });
    }

    long long maxArea = 0;

    while (!areas.empty()) {

        auto [area, UL, LR] = areas.top(); areas.pop();

        bool valid = true;

        for (auto& edge : edges) {

            auto [lA, lB] = edge;

            if (lA.first < LR.first && lB.first > UL.first &&
                lA.second < LR.second && lB.second > UL.second) {
                valid = false;
                break;
            }
        }

        if (valid) {
            maxArea = area;
            break;
        }
    }

    cout << "Part 2 Solution: " << maxArea << endl;
}

int main() {

    vector<pair<long long, long long>> data;
    readFile(data);

    Part1Solution(data);
    Part2Solution(data);
}
