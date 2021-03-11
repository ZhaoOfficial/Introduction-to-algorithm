#include <iostream>

using namespace std;

template <typename T>
class Stack
{
public:
	Stack(size_t capacity);
	~Stack();

	void push(T& value);
	T pop();
	void clear();

	bool empty() const;

private:
	size_t m_capacity;
	size_t m_top;
	T* m_data;
};

template <typename T>
Stack<T>::Stack(size_t capacity) : m_capacity(capacity), m_top(0)
{
	if (m_capacity < 100)
		m_capacity = 100;

	m_data = new T[m_capacity];
	while (m_data == nullptr)
		m_capacity = new T[m_capacity];
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] m_data;
}

template <typename T>
void Stack<T>::push(T& value)
{
	if (m_top < m_capacity)
		m_data[m_top++] = value;
	else
		cerr << "stack overflow\n";
}

template <typename T>
T Stack<T>::pop()
{
	if (m_top > 0)
		return m_data[m_top--];
	else
		cerr << "stack underflow\n";
}

template <typename T>
void Stack<T>::clear()
{
	m_top = 0;
}

template <typename T>
bool Stack<T>::empty() const
{
	return m_top == 0;
}