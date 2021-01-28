def partition1(array:list, low, high) -> int:
    pivot = array[high]
    i = low - 1
    for j in range(low, high):
        if array[j] < pivot:
            i += 1
            array[i], array[j] = array[j], array[i]
    array[i + 1], array[high] = array[high], array[i + 1]
    return i + 1

def quick_sort1(array:list, low, high):
    if low < high:
        mid = partition1(array, low, high)
        quick_sort1(array, low, mid - 1)
        quick_sort1(array, mid + 1, high)

def partition2(array:list, low, high) -> int:
    pivot = array[low]
    l = low
    r = high
    while l < r:
        while l < r and array[r] >= pivot:
            r -= 1
        array[l] = array[r]

        while l < r and array[l] <= pivot:
            l += 1
        array[r] = array[l]

    array[l] = pivot
    return l

def quick_sort2(array:list, low, high):
    if low < high:
        mid = partition2(array, low, high)
        quick_sort2(array, low, mid - 1)
        quick_sort2(array, mid + 1, high)


import time
import numpy as np

a = np.random.randint(0, 1000, 100000)
b = a.copy()

t = time.process_time()
quick_sort1(a, 0, len(a) - 1)
print(time.process_time() - t)

t = time.process_time()
quick_sort2(b, 0, len(b) - 1)
print(time.process_time() - t)

print(np.allclose(a, b))