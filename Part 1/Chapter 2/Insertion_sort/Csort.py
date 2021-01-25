import random
array = [random.randint(0, 20) for i in range(20)]
print(array)

for i in range(0, len(array)):
    minimal = i
    j = i
    while j < len(array):
        if array[j] < array[minimal]:
            minimal = j
        j += 1
    array[minimal], array[i] = array[i], array[minimal]

print(array)