from math import inf
import random

array = [random.randint(0, 20) for i in range(20)]
print(array)

def merge(array:list, begin, middle, end):
    L = array[begin:middle]
    R = array[middle:end]
    L.append(inf)
    R.append(inf)

    i = 0
    j = 0
    for k in range(begin, end):
        if L[i] <= R[j]:
            array[k] = L[i]
            i += 1
        else:
            array[k] = R[j]
            j += 1

def merge_sort(array:list, begin, end):
    if begin + 1 < end:
        middle = (begin + end) // 2
        merge_sort(array, begin, middle)
        merge_sort(array, middle, end)
        merge(array, begin, middle, end)
        
merge_sort(array, 0, len(array))
print(array)