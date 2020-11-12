# O(nlogn) actually it is O(n^2)
array = ['Place Holder', 5, 8, 9, 6, 7, 2, 3, 1, 4]
def insert_sort(array:list):
    for i in range(2, len(array)):
        temp = array[i]
        if temp < array[i - 1]:
            insertPoint = binary_search(1, i - 1, temp, array)
            for j in range(i, insertPoint, -1):
                array[j] = array[j - 1]
            array[insertPoint] = temp

def binary_search(lowerBound, upperBound, target, array) -> int:
    while lowerBound <= upperBound:
        middle = (lowerBound + upperBound) // 2
        if target < array[middle]:
            upperBound = middle - 1
        else:
            lowerBound = middle + 1
    return lowerBound

insert_sort(array)
print(array)
