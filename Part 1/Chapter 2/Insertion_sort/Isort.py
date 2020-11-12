array = ['Place Holder', 5, 8, 9, 6, 7, 2, 3, 1, 4]

for i in range(2, len(array)):
    temp = array[i]
    insertPoint = i - 1
    while insertPoint >= 1 and array[insertPoint] > temp:
        array[insertPoint + 1] = array[insertPoint]
        insertPoint -= 1
    array[insertPoint + 1] = temp

print(array)
