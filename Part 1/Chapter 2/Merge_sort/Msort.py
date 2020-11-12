from math import inf
# import random
array = ['Place Holder', 5, 8, 9, 6, 7, 2, 3, 1, 4]
# for i in range(10,1000000):
#     array.append(random.randint(10, 1000000))
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
        merge(array, begin, middle, end)
merge_sort(array, 1, len(array) - 1)
print(array)