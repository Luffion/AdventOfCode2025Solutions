#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void readFile(vector<vector<string>>& data) {
    ifstream myFile("data.txt");

    if (myFile.is_open()) {
        string line;

        while (getline(myFile, line)) {
            vector<string> row;
            stringstream ss(line);
            string word;
            while (ss >> word) {
                row.push_back(word);
            }
            data.push_back(row);
        }

        myFile.close();
    }
}

void readFile2(vector<string>& lines) {

    ifstream myFile("data.txt");

    if (myFile.is_open()) {
        string line;

        while (getline(myFile, line))
            lines.push_back(line);

        myFile.close();
    }

}

void Part1Solution(vector<vector<string>>& problems) {

    int problemsSize = problems.size();
    int problemSize = problems[0].size();
    vector<string> operators = problems[problemsSize - 1];

    long long sum = 0;
    for (int i = 0; i < problemSize; i++) {
        string op = operators[i];
        long long total = (op == "*") ? 1 : 0;
        for (int j = 0; j < problemsSize - 1; j++) {

            if (op == "+")
                total += stoll(problems[j][i]);
            else
                total *= stoll(problems[j][i]);
        }
        sum += total;
    }

    std::cout << "Part 1 Solution: " << sum << endl;
}

void Part2Solution(vector<string> rows) {

    string ops = rows[rows.size() - 1];
    
    int i = 0;
    int length = rows[0].length();
    string num = "";

    long long sum = 0; long long total = 0;
    char currentOp = '+';

    while (i < length) {

        char op = ops[i];
        num = "";
        if (op == '+' || op == '*') {
            sum += total;
            currentOp = op;
            total = (op == '*') ? 1 : 0;
        }

        for (int r = 0; r < rows.size() - 1; r++) {
            if (rows[r][i] != ' ') num += rows[r][i];
        }

        if (num.length()) {
            if (currentOp == '+')
                total += stoll(num);
            else if (currentOp == '*')
                total *= stoll(num);
        }


        i++;
    }

    sum += total;

    std::cout << "Part 2 Solution: " << sum << endl;

}

int main() {

    vector<vector<string>> data;
    readFile(data);

    vector<string> lines;
    readFile2(lines);

    Part1Solution(data);
    Part2Solution(lines);
}
