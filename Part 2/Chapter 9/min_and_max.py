import numpy as np

# find the minimum and maximum simultaneously
def min_and_max(a):
    n = len(a)
    start = 1
    if n % 2 == 0:
        minimum = min(a[0], a[1])
        maximum = max(a[0], a[1])
        start = 2
    else:
        minimum = a[0]
        maximum = a[0]

    for i in range(start, n, 2):
        if a[i] < a[i + 1]:
            temp_min = a[i]
            temp_max = a[i + 1]
        else:
            temp_min = a[i + 1]
            temp_max = a[i]
        
        if temp_min < minimum:
            minimum = temp_min
        if temp_max > maximum:
            maximum = temp_max

    return minimum, maximum


a = np.random.randint(0, 10000, 5000)
np.random.shuffle(a)
print(a)
print(min_and_max(a))

