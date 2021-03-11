#include <iostream>

using namespace std;

template <typename T>
class Queue {
public:
    Queue(size_t m_capacity);
    ~Queue();

    void push(T& value);
    T pop();
    void clear();

    bool empty() const;
private:
    size_t m_capacity;
    size_t m_head;
    size_t m_tail;
    T* m_data;

    inline size_t increment(size_t number)
    {
        return (number + 1) % m_capacity;
    }
};

template <typename T>
Queue<T>::Queue(size_t m_capacity) : m_capacity(m_capacity + 1), m_head(0), m_tail(0) {
    m_data = new T[m_capacity];
    while (m_data == nullptr)
        m_data = new T[m_capacity];
}

template <typename T>
Queue<T>::~Queue()
{
    if (m_data)
        delete[] m_data;
}

template <typename T>
void Queue<T>::push(T& value)
{
    if (increment(m_tail) != m_head)
    {
        m_data[m_tail++] = value;
        m_tail %= m_capacity;
    }
    else
        cerr << "queue overflow\n";
}

template <typename T>
T Queue<T>::pop()
{
    if (m_head != m_tail)
    {
        T res = m_data[m_head++];
        m_head %= m_capacity;
        return res;
    }
    else
        cerr << "queue underflow\n";
}

template <typename T>
void Queue<T>::clear()
{
    m_head = m_tail;
}

template <typename T>
bool Queue<T>::empty() const
{
    return m_head == m_tail;
}