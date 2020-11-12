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

    }

    void insert(Key key, Value value) {
        for (int i = 0; i < this->size; i++) {
            int j = hashfunction(key, i);
            if (table[j] == nullptr) {
                table[j] = new pairs<Key, Value>(key, value);
                return;
            }
        }
        cout << "hash table overflow." << endl;
    }

    pairs<Key, Value>* search(Key key) {
        for (int i = 0; i < this->size; i++) {
            int j = hashfunction(key, i);
            if (table[j] && table[j]->first == key) {
                return table[j];
            }
        }
        return nullptr;
    }
public:
    pairs<Key, Value>** table;
    int size;
};

int main() {

    return 0;
}
