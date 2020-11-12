from math import inf
array = ['Place Holder', 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, -7]

def find_max_crossing_subarray(array:list, low, mid, high):
    max_left = 0
    max_right = 0
    left_sum = -inf
    right_sum = -inf
    
    temp_sum = 0
    for i in range(mid, low - 1, -1):
        temp_sum += array[i]
        if temp_sum > left_sum:
            left_sum = temp_sum
            max_left = i

    temp_sum = 0
    for j in range(mid + 1, high + 1):
        temp_sum += array[j]
        if temp_sum > right_sum:
            right_sum = temp_sum
            max_right = j
    return (max_left, max_right, left_sum + right_sum)

def find_maximum_subarray(array:list, low, high):
    if low == high:
        return (low, high, array[low])
    else:
        mid = (low + high) // 2
        (left_low, left_high, left_sum) = find_maximum_subarray(array, low, mid)
        (right_low, right_high, right_sum) = find_maximum_subarray(array, mid + 1, high)
        (cross_low, cross_high, cross_sum) = find_max_crossing_subarray(array, low, mid, high)

    if left_sum == max(left_sum, right_sum, cross_sum):
        return (left_low, left_high, left_sum)
    elif right_sum == max(right_sum, cross_sum):
        return (right_low, right_high, right_sum)
    else:
        return (cross_low, cross_high, cross_sum)

import time
start = time.process_time()
print(find_maximum_subarray(array, 1, len(array) - 1))
print(time.process_time() - start)