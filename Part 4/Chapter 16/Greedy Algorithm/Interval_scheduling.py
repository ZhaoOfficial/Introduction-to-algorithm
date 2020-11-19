n = 11
startTime = [1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12]
# we arrange it with the ascending end time
endTime = [4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16]

def intervalSchedulingRecursive(startTime, endTime, n):
    if n == -1:
        return []
    
    index = n
    while index > -1 and endTime[index] > startTime[n]:
        index -= 1
    
    return intervalSchedulingRecursive(startTime, endTime, index) + [(startTime[n], endTime[n])]

def intervalSchedulingIterative(startTime, endTime, n):
    result = [(startTime[0], endTime[0])]

    k = 0
    for i in range(1, n):
        if startTime[i] >= endTime[k]:
            result.append((startTime[i], endTime[i]))
            k = i
    return result

print(intervalSchedulingRecursive(startTime, endTime, n - 1))
print(intervalSchedulingIterative(startTime, endTime, n))