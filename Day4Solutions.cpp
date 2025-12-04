#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

void readFile(vector<string>& data) {

    ifstream myFile("data.txt");

    if (myFile.is_open()) {
        string s;

        while (getline(myFile, s))
            data.push_back(s);

        myFile.close();
    }

}

void Part1Solution(vector<string>& grid) {

    int sum = 0;

    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] != '@') continue;
            int count = 0;
            for (int dr = -1; dr < 2; dr++) {
                for (int dc = -1; dc < 2; dc++) {

                    if (dr == 0 && dc == 0) continue;

                    int nr = row + dr;
                    int nc = col + dc;

                    if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[row].size()) {
                        if (grid[nr][nc] == '@') count++;
                    }

                }
            }
            if (count < 4) sum++;
        }
    }

    cout << "Part 1 solution: " << sum << endl;

}

void Part2Solution(vector<string>& grid) {

    int drs[8] = { -1,-1,-1, 0, 0, 1, 1, 1 };
    int dcs[8] = { -1, 0, 1,-1, 1,-1, 0, 1 };

    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> deg(rows, vector<int>(cols, 0));
    queue<pair<int, int>> q;

    for (int r = 0; r < rows; r++) {

        for (int c = 0; c < cols; c++) {

            if (grid[r][c] != '@') continue;

            int count = 0;
            for (int i = 0; i < 8; i++) {
                int nr = r + drs[i];
                int nc = c + dcs[i];

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    if (grid[nr][nc] == '@') count++;
                }
            }
            deg[r][c] = count;
            if (count < 4) q.push({r, c});
        }

    }

    int sum = 0;

    while (!q.empty()) {

        auto [r, c] = q.front(); q.pop();

        if (deg[r][c] == -1) continue;

        deg[r][c] = -1;
        sum++;

        for (int i = 0; i < 8; i++) {
            int nr = r + drs[i];
            int nc = c + dcs[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && deg[nr][nc] != -1) {
                deg[nr][nc]--;
                if (deg[nr][nc] < 4) q.push({ nr, nc });
            }

        }

    }

    cout << "Part 2 solution: " << sum << endl;
}

int main() {

    vector<string> data;
    readFile(data);

    Part1Solution(data);
    Part2Solution(data);
}
