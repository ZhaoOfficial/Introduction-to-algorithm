#include<iostream>
#include<vector>

using namespace std;

// Get input.
void Input(char expression[]) {

	cin >> expression[0];

	for (int index = 0; expression[index] != '#'; index++) {
		cin >> expression[index + 1];
	}
}

// Required character.
bool UNwanted(char input) {
	switch (input) {
	case('+'):
	case('-'):
	case('*'):
	case('/'):
	case('.'):
	case('('):
	case(')'):
	case('\n'):
	case(' '):
	case('\t'):
	case('1'):
	case('2'):
	case('3'):
	case('4'):
	case('5'):
	case('6'):
	case('7'):
	case('8'):
	case('9'):
	case('0'):
		return false;
	default:
		return true;
	}
}

// Transform in-fix notation to post-fix notation.
bool Transform(vector<char>& Origin, char expression[]) {

	char signal;
	vector<char> Sign;

	for (int index = 0; expression[index] != '#'; index++) {
		if (UNwanted(expression[index])) {
			printf("Please input numbers.\n");
			return false;
		}
		else if (isdigit(expression[index]) || expression[index] == '.') {
			Origin.push_back(expression[index]);
		}
		else if (expression[index] == '(') {
			Sign.push_back(expression[index]);
		}
		else if (expression[index] == ')') {
			signal = Sign.back();
			Sign.pop_back();
			while (signal != '(' && Sign.size()) {
				Origin.push_back(' ');
				Origin.push_back(signal);
				signal = Sign.back();
				Sign.pop_back();
			}
		}
		else if (expression[index] == '+' || expression[index] == '-') {
			if (Sign.size()) {
				do {
					signal = Sign.back();
					if (signal != '(') {
						Origin.push_back(' ');
						Sign.pop_back();
						Origin.push_back(signal);
					}
				} while (Sign.size() && signal != '(');
				Origin.push_back(' ');
				Sign.push_back(expression[index]);
			}
			else {
				Origin.push_back(' ');
				Sign.push_back(expression[index]);
			}
		}
		else if (expression[index] == '*' || expression[index] == '/') {
			Origin.push_back(' ');
			Sign.push_back(expression[index]);
		}
		else {
			continue;
		}
	}

	while (Sign.size()) {
		signal = Sign.back();
		Sign.pop_back();
		Origin.push_back(' ');
		Origin.push_back(signal);
	}
	Origin.push_back(' ');
	Origin.push_back('#');

	return true;
}


void Clear(char data[]) {
	for (int index = 0; index < 20; index++) {
		if (data[index])
			data[index] = '\0';
		else
			break;
	}
}

void Set(double &first, double &second, vector<double>& Polish) {
	first = Polish.back();
	Polish.pop_back();
	second = Polish.back();
	Polish.pop_back();
}

bool Calculate(vector<char>& Origin, vector<double>& Polish) {
	double first = 0, second = 0;
	char data[20] = "\0";
	int i = 0, j = 0;

	for (i = 0; Origin[i] != '#'; i++)
	{
		switch (Origin[i]) {
		case('+'):
			Set(first, second, Polish);
			Polish.push_back(second + first);
			break;
		case('-'):
			Set(first, second, Polish);
			Polish.push_back(second - first);
			break;
		case('*'):
			Set(first, second, Polish);
			Polish.push_back(second * first);
			break;
		case('/'):
			Set(first, second, Polish);
			if (first) {
				Polish.push_back(second / first);
			}
			else {
				printf("Error: divide 0.\n");
				return false;
			}
			break;
		case(' '):
			if (data[0]) {
				Polish.push_back(atof(data));
				Clear(data);
				j = 0;
			}
			break;
		default:
			if (isdigit(Origin[i]) || Origin[i] == '.') {
				for (j; j < 20; j++) {
					if (!data[j])
						break;
				}
				data[j] = Origin[i];
			}
			else {
				printf("Please input numbers.\n");
				return false;
			}
		}
	}
	return true;
}

int main() {

	vector<double> Polish;
	vector<char> Origin;
	char expression[100] = "\0";

	Input(expression);

	Transform(Origin, expression);

	if (!Calculate(Origin, Polish))
		return 0;
	
	if (Polish.size())
		cout << Polish[0];
	else
		printf("Please input numbers.\n");

	return 0;
}
