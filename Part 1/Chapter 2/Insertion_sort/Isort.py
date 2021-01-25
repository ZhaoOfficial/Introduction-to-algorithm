import random

array = [random.randint(0, 20) for i in range(20)]
print(array)

for i in range(1, len(array)):
    temp = array[i]
    insert_point = i - 1
    while insert_point >= 0 and array[insert_point] > temp:
        array[insert_point + 1] = array[insert_point]
        insert_point -= 1
    array[insert_point + 1] = temp

print(array)
