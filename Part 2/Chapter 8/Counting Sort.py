# 0 <= a[i] <= k
# a[i] != a[j]
import numpy as np
def CountingSort(A, k):
    # initialize
    B = np.zeros_like(A)
    C = np.zeros(k + 1, dtype = np.int)

    # C[i] is the number of elements that equals to i
    for i in range(len(A)):
       C[A[i]] += 1
    
    # C[i] is the number of elements that is smaller than i
    C = np.cumsum(C)
    
    # -1 for further adjustment
    for j in range(len(A) - 1, -1, -1):
        C[A[j]] -= 1
        B[C[A[j]]] = A[j]
    
    return B

a = np.random.randint(0, 100, 50)
np.random.shuffle(a)
print(a)
b = CountingSort(a, np.max(a))
print(b)