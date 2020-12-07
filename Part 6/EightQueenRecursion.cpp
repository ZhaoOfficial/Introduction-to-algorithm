#include<iostream>
#include<fstream>

using namespace std;

extern int count = 0;

bool Danger(int row, int col, int(*Copy)[8]) {
	int sum = row + col;
	int dif = row - col;
	//row
	for (int j = 0; j < row; j++) {
		if (Copy[j][col] == 1) {
			return true;
		}
	}
	//col
	if (sum <= 7) {
		for (int i = 0; sum - i > -1; i++) {
			if (Copy[sum - i][i] == 1) {
				return true;
			}
		}
	}
	else {
		for (int i = 7; sum - i < 8; i--) {
			if (Copy[sum - i][i] == 1) {
				return true;
			}
		}
	}
	//diag
	if (dif >= 0) {
		for (int i = 0; dif + i < 8; i++) {
			if (Copy[dif + i][i] == 1) {
				return true;
			}
		}
	}
	else {
		for (int i = 7; dif + i > -1; i--) {
			if (Copy[dif + i][i] == 1) {
				return true;
			}
		}
	}
	return false;
}

void Print(int(*Board)[8], const std::string& pathToRaw) {
	static int count;
	ofstream file;
	file.open(pathToRaw, ios::app);
	++count;
	cout << "The " << count << " th:" << endl;
	file << "The " << count << " th:" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << Board[i][j] << ' ';
			file << Board[i][j] << ' ';
		}
		cout << endl;
		file << endl;
	}
	cout << endl;
	file << endl;
	file.close();
}

void EightQueen(int row, int col, int(*Board)[8], const std::string& pathToRaw) {
	int Copy[8][8];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Copy[i][j] = Board[i][j];
		}
	}

	if (row == 8) {
		Print(Copy, pathToRaw);
	}
	else {
		for (int j = 0; j <= col; j++) {
			if (!Danger(row, j, Copy)) {
				Copy[row][j] = 1;

				EightQueen(row + 1, col, Copy, pathToRaw);
			
				Copy[row][j] = 0;
			}
		}
	}
}


int main() {
	int Board[8][8] = { 0 };
	const std::string pathToRaw = "result.txt";
	ofstream output;

	output.open(pathToRaw);

	output << "answer:\n";
	
	EightQueen(0, 7, Board, pathToRaw);

	output.close();

	return 0;
}
