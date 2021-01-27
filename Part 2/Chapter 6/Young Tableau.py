import numpy as np

class YoungTableau(object):
    def __init__(self, m, n):
        self.m = m
        self.n = n
        self.tableau = np.full((m, n), np.inf)
        
    def top(self):
        return self.tableau[0, 0]
    
    # similar to heap
    def pop(self):
        result = self.tableau[0, 0]
        self.tableau[0, 0] = np.inf
        
        r, c = 0, 0
        er, ec = 0, 0
        while True:
            if r + 1 < self.m and self.tableau[r + 1, c] < self.tableau[r, c]:
                er, ec = r + 1, c
            else:
                er, ec = r, c
            
            if c + 1 < self.n and self.tableau[r, c + 1] < self.tableau[er, ec]:
                er, ec = r, c + 1
            
            if er != r or ec != c:
                self.tableau[r, c], self.tableau[er, ec] = self.tableau[er, ec], self.tableau[r, c]
                r, c = er, ec
            else:
                break
        
        return result
    
    def push(self, value):
        self.tableau[-1, -1] = value
        r, c = self.m - 1, self.n - 1
        er, ec = 0, 0
        while True:
            if r > 0 and self.tableau[r, c] < self.tableau[r - 1, c]:
                er, ec = r - 1, c
            else:
                er, ec = r, c
            if c > 0 and self.tableau[er, ec] < self.tableau[r, c - 1]:
                er, ec = r, c - 1
            if er != r or ec != c:
                self.tableau[er, ec], self.tableau[r, c] = self.tableau[r, c], self.tableau[er, ec]
                r, c = er, ec
            else:
                break
    # the smaller is on left top side
    # the larger is on right bottom side
    # so we search the value along the anti-diagonal
    def find(self, value):
        r, c = 0, self.n - 1
        while r < self.m and c >= 0:
            if value < self.tableau[r, c]:
                c -= 1
            elif value > self.tableau[r, c]:
                r += 1
            else:
                return r, c
        return None
    
    def __getitem__(self, index):
        return self.tableau[index]
    
    def full(self):
        return self.tableau[-1, -1] == np.inf

    def empty(self):
        return self.tableau[0, 0] == np.inf

m, n = 4, 4
yt = YoungTableau(4, 4)
a = np.arange(m * n)
np.random.shuffle(a)
for i in a:
    yt.push(i)
print(yt.tableau)
print(yt.find(10))
while not yt.empty():
    print(yt.pop(), end = " ")