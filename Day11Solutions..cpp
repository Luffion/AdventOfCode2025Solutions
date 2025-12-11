#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
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

int dfs(string& k, unordered_map<string, vector<string>>& umap, unordered_map<string, int>& memo) {

    if (memo.count(k)) return memo[k];

    if (k == "out") return memo[k] = 1;

    int total = 0;
    for (string& s : umap[k])
        total += dfs(s, umap, memo);

    return memo[k] = total;
}

void Part1Solution(vector<string>& data) {

    unordered_map<string, vector<string>> umap;

    for (string& s : data) {

        int pos = s.find(':');

        string key;
        vector<string> temp;

        key = s.substr(0, pos);

        string rest = s.substr(pos+2);

        stringstream ss(rest);
        string token;

        while (ss >> token)
            temp.push_back(token);

        umap[key] = temp;
    }

    unordered_map<string, int> memo;

    string start = "you";

    int total = dfs(start, umap, memo);

    cout << "Part 1 Solution: " << total << endl;
}

long long dfs2(string& k, unordered_map<string, vector<string>>& umap, unordered_map<string, unordered_map<int, long long>>& memo, int seen) {

    if (memo[k].count(seen)) return memo[k][seen];

    if (k == "out") return memo[k][seen] = (seen == 3 ? 1LL : 0LL);

    if (k == "dac") seen |= 1;
    if (k == "fft") seen |= 2;

    long long total = 0;
    for (string& s : umap[k])
        total += dfs2(s, umap, memo, seen);

    return memo[k][seen] = total;
}

void Part2Solution(vector<string>& data) {

    unordered_map<string, vector<string>> umap;

    for (string& s : data) {

        int pos = s.find(':');

        string key;
        vector<string> temp;

        key = s.substr(0, pos);

        string rest = s.substr(pos + 2);

        stringstream ss(rest);
        string token;

        while (ss >> token)
            temp.push_back(token);

        umap[key] = temp;
    }

    unordered_map<string, unordered_map<int, long long>> memo;

    string start = "svr";

    long long total = dfs2(start, umap, memo, 0);

    cout << "Part 2 Solution: " << total << endl;
}

int main() {

    vector<string> data;

    readFile(data);

    Part1Solution(data);
    Part2Solution(data);
}
