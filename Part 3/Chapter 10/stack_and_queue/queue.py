class queue(object):
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
        
    def push_back(self, value):
        if self.__increase(self.tail) != self.head:
            self.data[self.tail] = value
            self.tail = self.__increase(self.tail)
        else:
            print("queue overflow")
            
    def pop_front(self):
        if self.head != self.tail:
            res = self.data[self.head]
            self.head = self.__increase(self.head)
            return res
        else:
            print("queue underflow")
            
    def clear(self):
        self.head = self.tail
            
q = queue(3)
for i in range(5):
    q.push_back(i)
    q.push_back(10*i)
    q.pop_front()
    print(q.head)
    print(q.tail)
    print(q.data)
q.clear()
q.pop_front()
