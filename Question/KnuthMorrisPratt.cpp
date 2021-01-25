#include<iostream>
#include<vector>

using namespace std;

class MyString {
public:
	MyString();
	MyString(char source[]);
	~MyString();
	int getSize()const;
	const char operator[](int index);

private:
	int m_size;
	vector<char> m_string;
};

MyString::MyString() {}

MyString::MyString(char source[]) {
	int index = 0;
	while (source[index] != '#') {
		this->m_string.push_back(source[index]);
		index++;
	}
	this->m_size = m_string.size();
}

int MyString::getSize() const {
	return this->m_size;
}

const char MyString::operator[](int index) {
	return this->m_string[index - 1];
}

MyString::~MyString() {

}

int KMP(MyString& source, MyString& sub) {

	int sourceLen = source.getSize();
	int subLen = sub.getSize();
	int place = -1;
	if (sourceLen == 0 || subLen == 0) {
		return place;
	}

	//Calculation of the next array.
	int prefix = 1;
	int suffix = 0;

	int* next = new int[subLen];
	next[0] = 0;
	
	while (prefix < subLen) {
		if (suffix == 0 || sub[prefix] == sub[suffix]) {
			prefix++;
			suffix++;
			if (sub[prefix] != sub[suffix]) {
				next[prefix - 1] = suffix;
			}
			else{
				next[prefix - 1] = next[suffix - 1];
			}
		}
		else {
			suffix = next[suffix - 1];
		}
	}


	//Find target.
	
	int subIndex = 1;
	int sourceIndex = 1;
	while (subIndex <= subLen || sourceIndex <= sourceLen) {
		if (sub[subIndex] == source[sourceIndex] || subIndex == 0) {
			subIndex++;
			sourceIndex++;
		}
		else {
			subIndex = next[subIndex - 1];
		}
	}

	if (subIndex > subLen) {
		place = sourceIndex - subLen;
	}

	//原因是我把next数组作为偏移索引的作用
	//而next数组记载的就应该是回溯的索引 
	//但是他的 Find target 找的是最后一次出现的子字符串 
	//可能是他记错了
	//等我再次学习时候再弄 
	
	//My code. 
	//Calculation of the next array.
	//被删掉了，反正很找的麻烦。 
	
	//Find target.
	
	/*next[0] = 1; 
	int diff = 0;
	for (; diff <= sourceLen - subLen;) {
		for (int subIndex = 1; subIndex <= subLen; subIndex++) {
			if (sub[subIndex] != source[subIndex + diff]) {
				diff += next[subIndex - 1];
				if (diff > sourceLen - subLen) {
					delete[]next;
					return place;
				}
				break;
			}
			if (subIndex == subLen) {
				place = diff + 1;
				delete[]next;
				return place;
			}
		}
	}*/ 
	
	delete[]next;
	return place;
}


int main() {

	cout << "End with #." << endl;

	char sourceString[200] = "/0";
	cout << "sourceString: ";
	cin >> sourceString[0];
	for (int index = 0; sourceString[index] != '#'; index++) {
		cin >> sourceString[index + 1];
	}

	char subString[100] = "/0";
	cout << "subString: ";
	cin >> subString[0];
	for (int index = 0; subString[index] != '#'; index++) {
		cin >> subString[index + 1];
	}

	MyString source(sourceString);
	MyString substring(subString);

	cout << "Index: " << KMP(source, substring);

	return 0;
}
