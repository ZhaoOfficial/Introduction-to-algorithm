#include<iostream>
#include<vector>

using namespace std;

bool Detect(int row, int col, int k, vector<vector<int> >& Board) {
	while (1) {
		switch (col) {
		case(0):
		case(3):
		case(6):
			for (int i = row; i < row + 3; i++) {
				for (int j = col; j < col + 3; j++) {
					if (Board[i][j] == k) {
						return true;
					}
				}
			}
			return false;
		default:
			col--;
			break;
		}
	}
}


bool Danger(int row, int col, int k, vector<vector<int> >& Board) {

	vector<vector<int> > Copy;
	Copy = Board;

	//row
	for (int i = 0; i < 9; i++) {
		if (Copy[row][i] == k) {
			return true;
		}
	}
	//col
	for (int j = 0; j < 9; j++) {
		if (Copy[j][col] == k) {
			return true;
		}
	}
	//around
	while (1) {
		switch (row) {
		case(0):
		case(3):
		case(6):
			return Detect(row, col, k, Copy);
		default:
			row--;
			break;
		}
	}

	return false;
}

void Print(vector<vector<int> >& Board) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << Board[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Sudoku(int index, vector<vector<int> >& Board) {
	vector<vector<int> > Copy;
	Copy = Board;

	int row, col;
	row = index / 9;
	col = index - 9 * row;

	if (index == 81) {
		Print(Copy);
		return;
	}
	else {
		if (Copy[row][col] == 0) {
			for (int k = 1; k < 10; k++) {
				if (!Danger(row, col, k, Copy)) {
					Copy[row][col] = k;
					Sudoku(index + 1, Copy);
					Copy[row][col] = 0;
				}
			}
		}
		else {
			//cout << index << endl;
			Sudoku(index + 1, Copy);
		}
	}
}


int main() {
	int Origin[81] =
//	{
//		0,0,0,1,0,0,0,3,7,
//		4,0,7,0,8,0,0,0,0,
//		0,0,0,0,0,0,1,0,0,
//		0,7,0,6,0,0,0,0,0,
//		0,0,0,0,5,0,4,0,0,
//		0,9,0,0,0,4,0,2,0,
//		0,4,5,0,0,0,0,0,9,
//		0,0,6,0,1,5,0,0,3,
//		9,0,3,0,0,2,0,0,0
//	};
	{
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	};

	vector<vector<int> > Board;
	vector<int> line;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			line.push_back(Origin[i * 9 + j]);
		}
		Board.push_back(line);
		line.clear();
	}

	cout << "answer:\n";

	Sudoku(0, Board);

	return 0;
}
