import random
# with sentinel
class linkedlist(object):
    def __init__(self, n):
        self.prevArray = [None] * (n + 1)
        self.dataArray = [None] * (n + 1)
        self.nextArray = [None] * (n + 1)
        self.capacity = n
        self.head = 0
        self.tail = 0
        
    def insert_front(self, value):
        pos = 1
        while self.prevArray[pos] is not None:
            pos = random.randrange(0, self.capacity)
        self.prevArray[pos] = self.tail
        self.dataArray[pos] = value
        self.nextArray[pos] = self.head
        self.prevArray[self.head] = pos
        self.nextArray[self.tail] = pos
        self.head = pos
        
    def insert_back(self, value):
        self.dataArray[self.tail] = value
        self.insert_front(None)
        self.head = self.nextArray[self.head]
        self.tail = self.nextArray[self.tail]
        
    def search(self, value):
        target = self.head
        while self.dataArray[target] is not None and self.dataArray[target] != value:
            target = self.nextArray[target] 
        return target
        
    def remove(self, value):
        target = self.search(value)
        if target != self.tail:
            self.prevArray[self.nextArray[target]] = self.prevArray[target]
            self.nextArray[self.prevArray[target]] = self.nextArray[target]
            self.prevArray[target] = None
            self.dataArray[target] = None
            self.nextArray[target] = None
        else:
            print("value not found")
            
    def printData(self):
        x = self.head
        data = []
        while x != self.tail:
            data.append(self.dataArray[x])
            x = self.nextArray[x]
        print(data)

l = linkedlist(15)
for i in range(1, 6):
    l.insert_front(i)
    l.insert_back(10 * i)
l.printData()
l.remove(20)
l.remove(25)
l.printData()
