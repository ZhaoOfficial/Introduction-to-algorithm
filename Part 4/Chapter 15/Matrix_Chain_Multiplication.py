# Given a chain <A1, A2,..., An> of n matrices, where matrix Ai has 
# dimension A_{i - 1}A_{i} , fully parenthesize the product A1A2...An 
# in a way that minimizes the number of scalar multiplications.

import math

def chain(A):
    n = len(A)
    m = [[0] * n for i in range(n)]
    s = [[0] * n for i in range(n)]

    # l is chain length
    for l in range(2, n):
        for i in range(1, n - l + 1):
            j = i + l -1
            m[i][j] = math.inf
            for k in range(i, j):
                q = m[i][k] + m[k + 1][j] + A[i - 1] * A[k] * A[j]
                if q < m[i][j]:
                    m[i][j] = q
                    s[i][j] = k
    
    return m, s

def parenthesize(s, i, j):
    if i == j:
        print("A_" + str(i), end = "")
    else:
        print("(", end = "")
        parenthesize(s, i, s[i][j])
        print("*", end = "")
        parenthesize(s, s[i][j] + 1, j)
        print(")", end = "")


A = [30, 35, 15, 5, 10, 20, 25]
n = len(A) - 1
m, s = chain(A)
print(m[1][n])
print(parenthesize(s, 1, n))