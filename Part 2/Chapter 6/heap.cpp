#include <iostream>
#include <vector>
#include <queue>

#include <memory.h>

using std::cin;
using std::cout;
using std::endl;
using std::swap;
using std::move;
using std::forward;
using std::vector;

auto left = [](int i) { return i << 1; };
auto right = [](int i) { return (i << 1) + 1; };
auto parent = [](int i) { return i >> 1; };

// using std::less<Type> to build a minimal heap
// using std::greater<Type> to build a maximal heap
template <typename Type, typename Functional>
class heap
{
public:
    heap();
    heap(vector<Type>& vec);
    ~heap();

    void push(const Type& value);
    void pop();
    Type& top();

    size_t size() const;
    bool empty() const;

    Type& operator[](size_t index);
private:
    void maintain(size_t index);

    vector<Type> m_container;
    Functional compare;
};

template <typename Type, typename Functional>
heap<Type, Functional>::heap() {
    m_container.resize(1);
}

template <typename Type, typename Functional>
heap<Type, Functional>::heap(vector<Type>& vec) {
    size_t n = vec.size();
    m_container.resize(1);
    m_container.insert(m_container.end(), vec.begin(), vec.end());
    for (size_t i = n / 2 + 1; i > 0; i--) {
        maintain(i);
    }
}

template <typename Type, typename Functional>
heap<Type, Functional>::~heap() {}

template <typename Type, typename Functional>
void heap<Type, Functional>::push(const Type& value) {
    size_t temp = m_container.size();
    m_container.emplace_back(value);
    while (temp > 1 and compare(m_container[temp], m_container[parent(temp)])) {
        swap(m_container[temp], m_container[parent(temp)]);
        temp = parent(temp);
    }
}

template <typename Type, typename Functional>
void heap<Type, Functional>::pop() {
    m_container[1] = m_container.back();
    m_container.pop_back();
    this->maintain(1);
}

template <typename Type, typename Functional>
Type& heap<Type, Functional>::top() {
    return m_container[1];
}

template <typename Type, typename Functional>
size_t heap<Type, Functional>::size() const {
    return m_container.size() - 1;
}

template <typename Type, typename Functional>
bool heap<Type, Functional>::empty() const {
    return m_container.size() == 1;
}

template <typename Type, typename Functional>
Type& heap<Type, Functional>::operator[](size_t index) {
    return m_container[index];
}

template <typename Type, typename Functional>
void heap<Type, Functional>::maintain(size_t index) {
    size_t l, r, extrema;
    // O(log n)
    while (index) {
        l = left(index);
        r = right(index);
        extrema = 0;
        if (l < m_container.size() and compare(m_container[l], m_container[index])) {
            extrema = l;
        }
        else {
            extrema = index;
        }

        if (r < m_container.size() and compare(m_container[r], m_container[extrema])) {
            extrema = r;
        }

        if (extrema != index) {
            swap(m_container[index], m_container[extrema]);
            index = extrema;
        }
        else
            break;
    }
}


int main()
{
    cout << "minimal heap\n";
    heap<int, std::less<int>> min_heap;
    cout << "Is heap empty: " << std::boolalpha << min_heap.empty() << endl;
    for (int i = 0; i < 10; i++) {
        min_heap.push(i * 2);
    }
    cout << "Heap size: " << min_heap.size() << endl;
    cout << "Is heap empty: " << std::boolalpha << min_heap.empty() << endl;
    cout << "Heap top: " << min_heap.top() << "\nHeap element: ";
    for (int i = 0; i < 10; i++) {
        cout << min_heap.top() << " ";
        min_heap.pop();
    }
    cout << "\n\n";

    cout << "maximal heap\n";
    heap<int, std::greater<int>> max_heap;
    cout << "Is heap empty: " << std::boolalpha << max_heap.empty() << endl;
    for (int i = 0; i < 10; i++) {
        max_heap.push(i * 2);
    }
    cout << "Heap size: " << max_heap.size() << endl;
    cout << "Is heap empty: " << std::boolalpha << max_heap.empty() << endl;
    cout << "Heap top: " << max_heap.top() << "\nHeap element: ";
    for (int i = 0; i < 10; i++) {
        cout << max_heap.top() << " ";
        max_heap.pop();
    }
    cout << "\n\n";

    cout << "test of vector constructor\n";
    vector<int> vec({ 17, 12, 15, 16, 9, 5, 8, 24, 29, 18, 23 });
    heap<int, std::less<int>> vec_heap(vec);
    cout << "Heap size: " << vec_heap.size() << endl;
    cout << "Is heap empty: " << std::boolalpha << vec_heap.empty() << endl;
    cout << "Heap top: " << vec_heap.top() << "\nHeap element: ";

    // actually, the pop order is a sorted order
    // time complexity: O(nlog n)
    while (not vec_heap.empty()) {
        cout << vec_heap.top() << " ";
        vec_heap.pop();
    }

    return 0;
}