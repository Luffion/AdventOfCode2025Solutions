#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Vec3 {
    int x, y, z;
};

void readFile(vector<Vec3>& data) {
    ifstream myFile("data.txt");
    string line;

    while (getline(myFile, line)) {

        size_t c1 = line.find(',');
        size_t c2 = line.find(',', c1 + 1);

        int x = stoi(line.substr(0, c1));
        int y = stoi(line.substr(c1 + 1, c2 - c1 - 1));
        int z = stoi(line.substr(c2 + 1));

        data.push_back({x, y, z});
    }
}

long long getSquaredDistance(Vec3 a, Vec3 b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

int find(int x, vector<int>& parent) {
    if (parent[x] != x)
        parent[x] = find(parent[x], parent);
    return parent[x];
}

void unite(int a, int b, vector<int>& parent, vector<int>& size) {
    a = find(a, parent);
    b = find(b, parent);

    if (a == b) return;

    if (size[a] < size[b]) swap(a, b);

    parent[b] = a;
    size[a] += size[b];
}

void Part1Solution(vector<Vec3>& junctions) {
    int n = junctions.size();
    vector<tuple<long long, int, int>> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({getSquaredDistance(junctions[i], junctions[j]), i, j });
        }
    }

    sort(edges.begin(), edges.end());

    vector<int> parent(n);
    vector<int> size(n, 1);
    for (int i = 0; i < n; i++) parent[i] = i;

    for (int i = 0; i < 1000; i++) {
        int u = get<1>(edges[i]);
        int v = get<2>(edges[i]);
        unite(u, v, parent, size);
    }

    long long largest1 = 0, largest2 = 0, largest3 = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] != i) continue;
        long long s = size[i];
        if (s > largest1) { largest3 = largest2; largest2 = largest1; largest1 = s; }
        else if (s > largest2) { largest3 = largest2; largest2 = s; }
        else if (s > largest3) { largest3 = s; }
    }

    long long total = largest1 * largest2 * largest3;

    cout << "Part 1 Solution: " << total << endl;
}

void Part2Solution(vector<Vec3>& junctions) {
    int n = junctions.size();
    vector<tuple<long long, int, int>> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({ getSquaredDistance(junctions[i], junctions[j]), i, j });
        }
    }

    sort(edges.begin(), edges.end());

    vector<int> parent(n);
    vector<int> size(n, 1);
    for (int i = 0; i < n; i++) parent[i] = i;

    int components = n;
    int x1 = -1, x2 = -1;

    for (auto& e : edges) {
        int u = get<1>(e);
        int v = get<2>(e);
        if (find(u, parent) != find(v, parent)) {
            if (components == 2) {
                x1 = u;
                x2 = v;
            }
            else if (components == 1)
                break;
            unite(u, v, parent, size);
            components--;
        }
    }

    long long product = (long long)junctions[x1].x * junctions[x2].x;

    cout << "Part 2 Solution: " << product << endl;
}

int main() {

    vector<Vec3> data;
    readFile(data);

    Part1Solution(data);
    Part2Solution(data);
}
