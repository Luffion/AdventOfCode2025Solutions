#include <iostream>
#include <string>
#include <vector>
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

void Part1Solution(vector<string>& banks) {

    int sum = 0;

    for (string& bank : banks) {

        int num = 0;
        int p = 0;

        for (int i = 0; i < bank.size()-1; i++) {
            int val = 10 * (bank[i] - '0');
            if (val > num) {
                num = val;
                p = i;
            }
        }

        int temp = 0;
        for (int i = p + 1; i < bank.size(); i++) {
            temp = max(bank[i] - '0', temp);
        }
        num += temp;

        sum += num;
    }

    cout << "Part 1 Solution: " << sum << endl;
}

void Part2Solution(vector<string>& banks) {

    long long sum = 0;

    for (string& bank : banks) {

        string num = "";

        int start = 0; int end = bank.size() - 11;

        for (int j = 0; j < 12; j++) {
            int max = 0; 
            end = bank.size() - 11 + j;

            for (int i = start; i < end; i++) {

                if (bank[i] - '0' > max) {
                    max = bank[i] - '0';
                    start = i + 1;
                }
            }
            num += max+'0';
        }

        sum += stoll(num);
    }

    cout << "Part 2 Solution: " << sum << endl;
}

int main() {

    vector<string> data;
    readFile(data);
    Part1Solution(data);
    Part2Solution(data);
}
