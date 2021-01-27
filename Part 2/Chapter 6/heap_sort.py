class Array(object):
    def __init__(self, data:list):
        self.data = data
        self.heapSize = len(data) - 1
        
    def __getitem__(self, index):
        return self.data[index]
        
    def __setitem__(self, index, value):
        self.data[index] = value

    def append(self, value):
        self.data.append(value)
        self.heapSize += 1

data = ['0', 88 ,85 ,83 ,72 ,73 ,42 ,57 ,11  ,48  ,60]

array = Array(data)

def parent(i):
    return i >> 1
    
def left(i):
    return i << 1
    
def right(i):
    return (i << 1) + 1

# maintain the max_heap
def max_heapify(array:Array, i):
    while (i):
        l = left(i)
        r = right(i)
        largest = 0
        
        if l <= array.heapSize and array[l] > array[i]:
            largest = l
        else:
            largest = i
        
        if r <= array.heapSize and array[r] > array[largest]:
            largest = r
            
        if largest != i:
            array[i], array[largest] = array[largest], array[i]
            # max_heapify(array, i)
            i = largest
        else:
            break
        
def min_heapify(array:Array, i):
    while (i):
        l = left(i)
        r = right(i)
        smallest = 0
        
        if l <= array.heapSize and array[l] < array[i]:
            smallest = l
        else:
            smallest = i
        
        if r <= array.heapSize and array[r] < array[smallest]:
            smallest = r
            
        if smallest != i:
            array[i], array[smallest] = array[smallest], array[i]
            # min_heapify(array, i)
            i = smallest
        else:
            break

def build_max_heap(array:Array):
    for i in range(array.heapSize // 2, 0, -1):
        max_heapify(array, i)
        
def build_min_heap(array:Array):
    for i in range(array.heapSize // 2, 0, -1):
        min_heapify(array, i)

def heap_sort(array:Array):
    build_max_heap(array)
    for i in range(array.heapSize, 1, -1):
        array[1], array[i] = array[i], array[1]
        array.heapSize -= 1
        max_heapify(array, 1)
        print(array.data)

def max_heap_push(array:Array, value):
    array.append(value)
    index = array.heapSize
    while index > 1:
        if array[index] > array[parent(index)]:
            array[index], array[parent(index)] = array[parent(index)], array[index]
            index = parent(index)
        else:
            break

def max_heap_pop(array:Array, index):
    value = array[index]
    array[index] = array[-1]
    array.data.pop(-1)
    array.heapSize -= 1
    max_heapify(array, index)
    return value

heap_sort(array)
print(array.data)
