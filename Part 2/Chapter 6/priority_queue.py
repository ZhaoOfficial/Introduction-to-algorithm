class Array(object):
    def __init__(self, data:list):
        self.data = data
        self.heapSize = len(data) - 1
        
    def __getitem__(self, index):
        return self.data[index]
        
    def __setitem__(self, index, value):
        self.data[index] = value

data = ['0', 8, 10, 9, 6, 4, 16, 5, 13, 26, 18, 2, 45, 34, 23, 1, 7, 3]

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
        
def build_max_heap(array:Array):
    for i in range(array.heapSize // 2, 0, -1):
        max_heapify(array, i)
        
def heap_sort(array:Array):
    build_max_heap(array)
    for i in range(array.heapSize, 1, -1):
        array[1], array[i] = array[i], array[1]
        array.heapSize -= 1
        max_heapify(array, 1)

def heap_maximum(array:Array):
    return array[1]
    
def heap_extract_max(array:Array):
    if array.heapSize < 1:
        print("heap underflow")
        return
    maxvalue = array[1]
    array[1] = array[array.heapSize]
    array.heapSize -= 1
    max_heapify(array, 1)
    return maxvalue
    
def heap_increase_key(array:Array, i, key):
    if key < array[i]:
        print("new key is smaller than current key")
        return
    array[i] = key
    while i > 1 and array[parent(i)] < array[i]:
        array[parent(i)], array[i] = array[i], array[parent(i)]
        i = parent(i)
        
def max_heap_insert(array:Array, key):
    import math
    array.heapSize += 1
    array.data.append(-math.inf)
    heap_increase_key(array, array.heapSize, key)
    
build_max_heap(array)
print(heap_extract_max(array))
print(array.data) 
