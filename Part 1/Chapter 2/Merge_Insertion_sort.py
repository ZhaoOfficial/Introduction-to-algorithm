from math import inf
import random
array = ['Place Holder']
for i in range(10,100000):
    array.append(random.randint(10, 100000))
def merge(array:list, begin, middle, end):
    n1 = middle - begin + 1
    n2 = end - middle
    L = ['Place Holder']
    R = ['Place Holder']
    for i in range(1, n1 + 1):
        L.append(array[begin + i - 1])
    for j in range(1, n2 + 1):
        R.append(array[middle + j])
    L.append(inf)
    R.append(inf)
    i = 1
    j = 1
    for k in range(begin, end + 1):
        if L[i] <= R[j]:
            array[k] = L[i]
            i += 1
        else:
            array[k] = R[j]
            j += 1

def merge_sort(array:list, begin, end):
    if begin < end:
        middle = (begin + end) // 2
        merge_sort(array, begin, middle)
        merge_sort(array, middle + 1, end)
        if end - begin <= 32:
            insertion_sort(array, begin, end)
        else:
            merge(array, begin, middle, end)

def insertion_sort(array, begin, end):
    for i in range(begin + 1, end + 1):
        temp = array[i]
        insertPoint = i - 1
        while insertPoint >= begin and array[insertPoint] > temp:
            array[insertPoint + 1] = array[insertPoint]
            insertPoint -= 1
        array[insertPoint + 1] = temp

merge_sort(array, 1, len(array) - 1)
print(array)
