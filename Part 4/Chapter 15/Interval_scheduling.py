n = 7
startTime = [1, 3, 0, 4, 3, 5, 6, 8]
# we arrange it with the ascending end time
endTime = [4, 5, 6, 7, 8, 9, 10, 11]
value = [5, 1, 8, 4, 6, 3, 2, 4]

array = [None] * (n + 1)

# O(n)
def intervalScheduling(startTime, endTime, value, n):
    if n < 0:
        return 0
    
    if array[n] is None:
        # index find the feasible task
        index = n
        while index > -1 and endTime[index] > startTime[n]:
            index -= 1
        
        array[n] = max(intervalScheduling(startTime, endTime, value, index)
            + value[n], intervalScheduling(startTime, endTime, value, n - 1))
    
    return array[n]

print(intervalScheduling(startTime, endTime, value, n))