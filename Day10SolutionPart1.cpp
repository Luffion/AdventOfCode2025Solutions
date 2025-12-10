#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>

using namespace std;

struct Machine {
    string lights;
    vector<vector<int>> wirings;
    vector<int> joltages;
};

void readFile(vector<Machine>& machines) {
    ifstream in("data.txt");
    if (!in.is_open()) return;
    auto parseInts = [](const string& s) {
        vector<int> out; string tok; stringstream ss(s);
        while (getline(ss, tok, ',')) if (!tok.empty()) out.push_back(stoi(tok));
        return out;
        };
    string line;
    while (getline(in, line)) {
        Machine m;
        for (size_t i = 0;i < line.size();) {
            if (line[i] == '[') { size_t j = line.find(']', i); if (j == string::npos) break; m.lights = line.substr(i + 1, j - i - 1); i = j + 1; }
            else if (line[i] == '(') { size_t j = line.find(')', i); if (j == string::npos) break; m.wirings.push_back(parseInts(line.substr(i + 1, j - i - 1))); i = j + 1; }
            else if (line[i] == '{') { size_t j = line.find('}', i); if (j == string::npos) break; m.joltages = parseInts(line.substr(i + 1, j - i - 1)); i = j + 1; }
            else ++i;
        }
        machines.push_back(move(m));
    }
}

void Part1Solution(vector<Machine>& machines) {

    int result = 0;

    for (auto& machine : machines) {

        int size = machine.lights.size();

        int target = 0;
        for (int i = 0; i < size; i++) {
            if (machine.lights[i] == '#')
                target |= (1 << i);
        }

        size = machine.wirings.size();
        vector<int> masks(size, 0);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < machine.wirings[i].size(); j++)
                masks[i] |= (1 << machine.wirings[i][j]);
        }

        vector<int> dist(1 << machine.lights.size(), -1);
        queue<int> q;

        dist[0] = 0;
        q.push(0);

        int minPresses = -1;

        while (!q.empty()) {

            int state = q.front(); q.pop();

            if (state == target) {
                minPresses = dist[state];
                break;
            }

            for (int i = 0; i < size; i++) {
                int next = state ^ masks[i];
                if (dist[next] == -1) {
                    dist[next] = dist[state] + 1;
                    q.push(next);
                }
            }

        }

        result += minPresses;
    }

    cout << "Part 1 Solution: " << result << endl;
}

int main() {

    vector<Machine> machines;

    readFile(machines);

    Part1Solution(machines);

}
