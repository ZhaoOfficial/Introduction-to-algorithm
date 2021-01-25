# O(nlogn) actually it is O(n^2)
import random

array = [random.randint(0, 20) for i in range(20)]
print(array)

def insert_sort(array:list):
    for i in range(1, len(array)):
        temp = array[i]
        if temp < array[i - 1]:
            insert_point = binary_search(0, i - 1, temp, array)
            for j in range(i, insert_point, -1):
                array[j] = array[j - 1]
            array[insert_point] = temp

def binary_search(low, high, target, array) -> int:
    while low <= high:
        mid = (low + high) // 2
        if target < array[mid]:
            high = mid - 1
        else:
            low = mid + 1
    return low

insert_sort(array)
print(array)
