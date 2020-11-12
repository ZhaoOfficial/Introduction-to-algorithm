class stack(object):
    def __init__(self, n):
        self.capacity = n
        self.data = ["0"] * n
        self.top = 0
        
    def empty(self) -> bool:
        return not bool(self.top)
    
    def push_back(self, value):
        if self.top < self.capacity:
            self.data[self.top] = value
            self.top += 1
        else:
            print("stack overflow")
            
    def pop_back(self):
        if self.top > 0:
            self.top -= 1
            return self.data[self.top]
        else:
            print("stack underflow")
            
    def clear(self):
        self.top = 0
    
    def printData(self):
        print(self.data[0:self.top])

s = stack(5)
for i in range(7):
    s.printData()
    s.push_back(i)
s.clear()
s.pop_back()
