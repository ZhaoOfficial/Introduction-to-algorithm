from math import inf
array = [13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, -7]

def find_maximum_subarray(array:list, low, high):
    temp_sum = 0
    left_bound, right_bound = low, low
    subarray_sum = -inf
    sub_left_bound = low
    for i in range(low, high):
        temp_sum += array[i]
        if temp_sum > subarray_sum:
            subarray_sum = temp_sum
            left_bound = sub_left_bound
            right_bound = i
        if temp_sum < 0:
            temp_sum = 0
            sub_left_bound = i + 1
    return (left_bound, right_bound, subarray_sum)

print(find_maximum_subarray(array, 0, len(array)))