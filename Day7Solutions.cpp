#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const noexcept {
        return ((size_t)p.first << 32) ^ (size_t)p.second;
    }
};

void readFile(vector<string>& lines) {

    ifstream myFile("data.txt");

    if (myFile.is_open()) {
        string line;

        while (getline(myFile, line))
            lines.push_back(line);

        myFile.close();
    }

}

void Part1Solution(vector<string>& grid) {

    queue<pair<int, int>> q;
    unordered_set<pair<int, int>, PairHash> seen;

    int rows = grid.size();
    q.push({0, rows/2 - 1});

    int sum = 0;

    while (!q.empty()) {

        auto [row, col] = q.front(); q.pop();

        while (row < rows - 1 && grid[row][col] != '^')
            row++;

        if (grid[row][col] == '^') {

            if (!seen.count({ row, col })) {
                seen.insert({ row, col });
                sum++;
            }

            if (!seen.count({row, col-1})) {
                seen.insert({row, col-1});
                q.push({row, col-1});
            }
            if (!seen.count({ row, col + 1 })) {
                seen.insert({ row, col + 1 });
                q.push({ row, col + 1 });
            }
        }
    }

    std::cout << "Part 1 Solution: " << sum << endl;
}

long long dfs(vector<string>& grid, pair<int, int> coords, unordered_map<pair<int,int>, long long, PairHash>& memo) {

    auto [row, col] = coords;
    if (row == grid.size() - 1)
        return 1;

    if (memo.count(coords))
        return memo[coords];

    long long total = 0;

    if (grid[row][col] == '^') {
        total += dfs(grid, { row, col - 1 }, memo);
        total += dfs(grid, { row, col + 1 }, memo);
    }
    else {
        total += dfs(grid, { row + 1, col }, memo);
    }

    memo[coords] = total;
    return total;

}

void Part2Solution(vector<string>& grid) {

    unordered_map<pair<int, int>, long long, PairHash> memo;
    long long sum = dfs(grid, { 0, grid.size() / 2 - 1 }, memo);

    std::cout << "Part 2 Solution: " << sum << endl;

}

int main() {

    vector<string> data;
    readFile(data);

    Part1Solution(data);
    Part2Solution(data);
}
