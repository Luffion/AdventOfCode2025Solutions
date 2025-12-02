#include <iostream>
#include <string>
#include <sstream>
#include<vector>
#include<fstream>

using namespace std;

void readFile(vector<pair<string, string>>& data) {

    ifstream myFile("data.txt");

    if (myFile.is_open()) {
        string value;

        while (getline(myFile, value, ',')) {
            int pos = value.find('-');

            data.emplace_back(value.substr(0, pos), value.substr(pos + 1));
        }

        myFile.close();
    }

}

void Part1Solution(vector<pair<string, string>>& ranges) {

    long long invalid_ids = 0;
    for (auto [s_num1, s_num2] : ranges) {

        long long num1 = stoll(s_num1); 
        long long num2 = stoll(s_num2);

        for (long long i = num1; i <= num2; i++) {
            string temp = to_string(i);
            int size = temp.length();
            if (size % 2 == 0){

                if (temp.substr(0,size/2) == temp.substr(size/2)) invalid_ids+=i;

            }

        }

    }

    cout << "Part 1 solution: " << invalid_ids << endl;

}

void Part2Solution(vector<pair<string, string>>& ranges) {

    long long invalid_ids = 0;
    for (auto [s_num1, s_num2] : ranges) {

        long long num1 = stoll(s_num1);
        long long num2 = stoll(s_num2);

        for (long long i = num1; i <= num2; i++) {
            string temp = to_string(i);
            int size = temp.length();

            string doubled = temp + temp;
            string sub = doubled.substr(1, 2 * size - 2);

            if (sub.find(temp) != string::npos) {
                invalid_ids += i;
            }

        }

    }

    cout << "Part 2 solution: " << invalid_ids << endl;

}

int main() {
    vector<pair<string, string>> data;
    readFile(data);

    Part1Solution(data);
    Part2Solution(data);
}
