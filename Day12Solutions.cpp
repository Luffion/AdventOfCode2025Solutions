#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

void readFile(vector<pair<int, int>>& dims, vector<vector<int>>& values) {
    
    ifstream myFile("data.txt");

    string line;

    while (getline(myFile, line)) {

        stringstream ss(line);
        string dimPart;
        ss >> dimPart;

        if (dimPart.back() == ':')
            dimPart.pop_back();

        int w, h;
        char x;
        stringstream ds(dimPart);

        ds >> w >> x >> h;

        dims.emplace_back(w, h);


        vector<int> nums;
        int n;
        while (ss >> n)
            nums.push_back(n);

        values.push_back(nums);
    }
}

void Part1Solution(vector<pair<int, int>>& dims, vector<vector<int>>& values) {

    vector<int> shapes = { 7, 6, 7, 7, 7, 5 };

    int size = dims.size();

    int total = 0;
    for (int i = 0; i < size; i++) {

        auto [x, y] = dims[i];
        int area = x * y;

        for (int j = 0; j < values[i].size(); j++) {
            area -= shapes[j] * values[i][j];
        }

        if (area >= 0) total++;
    }

    cout << "Part 1 Solution: " << total << endl;
}


int main() {

    vector<pair<int, int>> dims;
    vector<vector<int>> values;

    readFile(dims, values);

    Part1Solution(dims, values);
}
