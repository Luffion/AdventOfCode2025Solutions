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

void Part1Solution(vector<string>& instructions) {

	int dial = 50;
	int password = 0;

	for (string instruction : instructions) {
		
		int change = stoi(instruction.substr(1));
		instruction[0] == 'L' ? dial -= change : dial += change;
		

		while (dial < 0 || dial > 99) {
			if (dial < 0)
				dial += 100;
			else if (dial > 99)
				dial -= 100;
		}

		if (dial == 0)
			password++;
	}

	cout << "Part 1 solution: " << password << endl;
}

void Part2Solution(vector<string>& instructions) {

	int dial = 50;
	int password = 0;

	for (string instruction : instructions) {

		char direction = instruction[0];
;		int change = stoi(instruction.substr(1));
		
		int start = dial;
		int count = 0;

		int offset;
		direction == 'L' ? offset = start % 100 : offset = (100 - start) % 100;

		if (offset == 0)
			count = change / 100;
		else {
			if (change >= offset)
				count = 1 + (change - offset) / 100;
		}

		dial = (direction == 'R') ? (dial + (change % 100)) % 100 : (dial - (change % 100) + 100) % 100;
	
		password += count;
	}

	cout << "Part 2 solution: " << password << endl;
}

int main() {

	vector<string> data;
	readFile(data);

	Part1Solution(data);
	Part2Solution(data);
}
