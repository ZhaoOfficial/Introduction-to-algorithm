n = 7
startTime = [1, 3, 0, 4, 3, 5, 6, 8]
endTime = [4, 5, 6, 7, 8, 9, 10, 11]
value = [5, 1, 8, 4, 6, 3, 2, 4]

def intervalScheduling(startTime, endTime, value, n):
    if n < 0:
        return 0
    
    index = n
    while index > -1 and endTime[index] > startTime[n]:
        index -= 1
    
    return max(intervalScheduling(startTime, endTime, value, index) + value[n], intervalScheduling(startTime, endTime, value, n - 1))

print(intervalScheduling(startTime, endTime, value, n))