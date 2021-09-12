import math

price = [0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30]

#! top-down with memoization
def Cut_rod_top_down(length):
    
    memo = [-math.inf for i in range(length + 1)]
    cut = [0 for i in range(length + 1)]

    top_down(length, memo, cut)

    return memo[length], cut_solution(cut, length)


def top_down(length, memo, cut):
    if memo[length] >= 0:
        return memo[length]

    if length == 0:
        p = 0
    else:
        p = -math.inf
        for i in range(1, length + 1):
            if i > 10:
                value = price[10]
            else:
                value = price[i]
            if p < value + top_down(length - i, memo, cut):
                p = value + top_down(length - i, memo, cut)
                # only memoize where to cut first
                cut[length] = i
    
    memo[length] = p

    return p

#! bottom-up
def Cut_rod_bottom_up(length):
    memo = [0 for i in range(length + 1)]
    cut = [0 for i in range(length + 1)]

    for i in range(1, length + 1):
        p = -math.inf
        for j in range(1, i + 1):
            if j > 10:
                value = price[10]
            else:
                value = price[j]
            if p < value + memo[i - j]:
                p = value + memo[i - j]
                cut[i] = j
            
        memo[i] = p
    return memo[length], cut_solution(cut, length)

def cut_solution(cut, length):
    rots = []
    while length > 0:
        rots.append(cut[length])
        length -= cut[length]
    return rots

print(Cut_rod_top_down(9))
print(Cut_rod_bottom_up(8))