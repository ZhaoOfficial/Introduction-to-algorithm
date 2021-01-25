import random

array = [random.randint(0, 20) for i in range(20)]
print(array)

for i in range(0, len(array)):
    for j in range(len(array) - 1, i, -1):
        if array[j] < array[j - 1]:
            array[j], array[j - 1] = array[j - 1], array[j]
            
print(array)