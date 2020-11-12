class deque(object):
    def __init__(self, n):
        self.capacity = n + 1
        self.data = ["0"] * self.capacity
        self.head = 0
        self.tail = 0
    
    def __increase(self, number):
        res = number
        res += 1
        res %= self.capacity
        return res
        
    def __decrease(self, number):
        res = number
        res += (self.capacity - 1)
        res %= self.capacity
        return res
        
    def push_back(self, value):
        if self.__increase(self.tail) != self.head:
            self.data[self.tail] = value
            self.tail = self.__increase(self.tail)
        else:
            print("deque overflow")
    
    def push_front(self, value):
        if self.__decrease(self.head) != self.tail:
            self.head = self.__decrease(self.head)
            self.data[self.head] = value
        else:
            print("deque overflow")
            
    def pop_front(self):
        if self.head != self.tail:
            res = self.data[self.head]
            self.head = self.__increase(self.head)
            return res
        else:
            print("deque underflow")
            
    def pop_back(self):
        if self.head != self.tail:
            res = self.data[self.tail]
            self.tail = self.__decrease(self.tail)
            return res
        else:
            print("deque underflow")
            
    def clear(self):
        self.head = self.tail
            
q = deque(3)
for i in range(1, 5):
    q.push_front(i)
    q.push_front(10*i)
    q.pop_back()
    print(q.head)
    print(q.tail)
    print(q.data)
q.clear()
q.pop_back()
