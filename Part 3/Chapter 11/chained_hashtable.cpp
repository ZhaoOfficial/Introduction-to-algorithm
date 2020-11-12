#include <iostream>

using namespace std;

template <typename Key, typename Value>
class pairs {
public:
    pairs(Key key, Value value, pairs<Key, Value>* prev = nullptr, pairs<Key, Value>* next = nullptr):
        first(key), second(value), prev(prev), next(next) {}

    pairs<Key, Value>* prev;
    Key first;
    Value second;
    pairs<Key, Value>* next;
    friend ostream& operator<<(ostream& os, pairs<Key, Value>& p) {
    	return os << p.first << ' ' << p.second;
	}
};

template <typename Key, typename Value>
class hashtable {
public:
    hashtable(int size) {
        this->table = new pairs<Key, Value>*[size];
        for (int i = 0; i < size; i++) {
            this->table[i] = nullptr;
        }
        this->size = size;
    }
    ~hashtable() {
        for (int i = 0; i < size; i++) {
            if(this->table[i]) {
                delete this->table[i];
            }
        }
        delete[] this->table;
    }

    int hashfunction1(Key key) {
        // module
        return key % this->size;
        // it is not fit when size = 2^n
        // since it will increase the probability of collision
    }
    int hashfunction2(Key key) {
        // mutiply
        return ((key * 0.6180339887) - floor(key * 0.6180339887)) * this->size;
        // size is not the key part of the hash function
        // 0.6180339887 may be a good choice
    }
    int hashfunction3(Key key) {
        // universal
        int a = 18;
        int b = 5;
        int p = 31;
        return (a * key + b) % p % this->size;
        // a function is universal if it maps
        // n elements into m slots averagely
        // p-ring
    }

    pairs<Key, Value>* direct_address_search(int pos) {
        pos = hashfunction1(pos);
        return this->table[pos];
    }
    void direct_address_insert(int pos, Key key, Value value) {
        pos = hashfunction1(pos);
        pairs<Key, Value>* node = new pairs<Key, Value>(key, value);
        this->table[pos] = node;
    }
    void direct_address_delete(int pos) {
        pos = hashfunction1(pos);
        if (this->table[pos]) {
            delete this->table[pos];
            this->table[pos] = nullptr;
        }
    }
public:
    pairs<Key, Value>** table;
    int size;
};

int main() {
	hashtable<int, char> ht(10);
	for (int i = 0; i < 9; i++) {
		ht.direct_address_insert(0 + i, 0 + i, (char)('a' + i));
	}
    for (int i = 0; i < 10; i++) {
    	if (ht.direct_address_search(0 + i))
			cout << *(ht.direct_address_search(0 + i)) << endl;
	}
    return 0;
}
