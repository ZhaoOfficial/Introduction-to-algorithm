class node(object):
    def __init__(self, data, prev, next):
        self.data = data
        self.prev = prev
        self.next = next

class linkedlist(object):
    def __init__(self):
        self.head = node(None, None, None)
        self.head.prev = self.head
        self.head.next = self.head
        self.tail = self.head
        
    def search(self, value):
        target = self.head
        while target.data is not None and target.data != value:
            target = target.next
        return target
        
    def insert_front(self, data):
        new = node(data, self.tail, self.head)
        self.head.prev = new
        self.tail.next = new
        self.head = new

    def insert_back(self, data):
        self.tail.data = data
        self.insert_front(None)
        self.tail = self.tail.next
        self.head = self.head.next
        
    def remove(self, value):
        target = self.search(value)
        if target.data is not None:
            target.next.prev = target.prev
            target.prev.next = target.next
        else:
            print("value not found")
            
    def printData(self):
        x = self.head
        data = []
        while x != self.tail:
            data.append(x.data)
            x = x.next
        print(data)
            
l = linkedlist()
for i in range(5):
    l.insert_front(i)
    l.insert_back(10 * i)
l.printData()
l.remove(20)
l.remove(25)
l.printData()
