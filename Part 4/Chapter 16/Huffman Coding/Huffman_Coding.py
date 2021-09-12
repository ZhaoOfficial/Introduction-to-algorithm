# variable length code
# prefix code 

# If C is the alphabet, then the tree
# which the optimal prefix code represents
# contains |C| leaves and |C| - 1 nodes.

# B(T) = \Sigma_{c\in C} c.frequency * d_T(c)

# Greedy algorithm
# priority queue
# ----------------------------------------------------------------
import copy

def quicksort(array, low, high):
    if low < high:
        pivot = array[high][1]
        i = low - 1
        for j in range(low, high):
            if array[j][1] < pivot:
                i += 1
                array[i], array[j] = array[j], array[i]
        array[i + 1], array[high] = array[high], array[i + 1]
        mid = i + 1
        quicksort(array, low, mid - 1)
        quicksort(array, mid + 1, high)

def parent(i):
    return i >> 1
    
def left(i):
    return i << 1
    
def right(i):
    return (i << 1) + 1

class Array(object):
    def __init__(self, data:list):
        self.data = data
        self.heapSize = len(data) - 1
        
    def __getitem__(self, index):
        return self.data[index]
        
    def __setitem__(self, index, value):
        self.data[index] = value

def heap_extract_min(array:Array):
    if array.heapSize < 1:
        print("heap underflow")
        return
    minValue = array[1]
    array[1] = array[array.heapSize]
    array.heapSize -= 1
    min_heapify(array, 1)
    array.data.pop()
    return minValue

def min_heapify(array:Array, i):
    while (i):
        l = left(i)
        r = right(i)
        smallest = 0
        
        if l <= array.heapSize and array[l][1] < array[i][1]:
            smallest = l
        else:
            smallest = i
        
        if r <= array.heapSize and array[r][1] < array[smallest][1]:
            smallest = r
            
        if smallest != i:
            array[i], array[smallest] = array[smallest], array[i]
            # min_heapify(array, i)
            i = smallest
        else:
            break

def min_heap_push(array:Array, value):
    array.data.append(value)
    array.heapSize += 1
    index = array.heapSize
    while index > 1:
        if array[index][1] < array[parent(index)][1]:
            array[index], array[parent(index)] = array[parent(index)], array[index]
            index = parent(index)
        else:
            break

class node(object):
    def __init__(self, data = None, left = None, right = None):
        self.data = data
        self.left = left
        self.right = right
    
    def __getitem__(self, index):
        return self.data[index]
        
    def __setitem__(self, index, value):
        self.data[index] = value

    def __str__(self, string = ''):
        result = ''
        if self.left is None and self.right is None:
            return str(self.data[0]) + '  ' + string + '\n'
        else:
            result += self.left.__str__(string + '0')
            result += self.right.__str__(string + '1')
 
        return result


C = Array(['0', node(('12', 12)), node(('10', 10)), node(('7', 7)), 
    node(('5', 5)), node(('4', 4)), node(('2', 2))])

# O(nlogn)
def Huffman(C):
    n = len(C.data) - 1
    queue = copy.deepcopy(C)
    quicksort(queue, 1, n)

    for _ in range(1, n):
        newNode = node()
        newNode.left = heap_extract_min(queue)
        newNode.right = heap_extract_min(queue)
        newNode.data = ('node', newNode.left[1] + newNode.right[1])
        min_heap_push(queue, newNode)
    return heap_extract_min(queue)

result = Huffman(C)
print(result)
