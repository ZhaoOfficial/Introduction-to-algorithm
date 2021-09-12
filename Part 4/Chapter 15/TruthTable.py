TFList = [True, False, True, False]
op = ['or', 'or', 'and']

n = len(TFList)

T = [[0] * n for _ in range(n)]
F = [[0] * n for _ in range(n)]

for i in range(n):
    if TFList[i] == True:
        T[i][0] = 1
    else:
        F[i][0] = 1

for j in range(1, n):
    for k in range(0, j):
        for i in range(0, n - j):
            if op[i + k] == 'and':
                T[i][j] += T[i][k] * T[i + k + 1][j - k - 1]
                F[i][j] += (F[i][k] * F[i + k + 1][j - k - 1] + T[i][k] * F[i + k + 1][j - k - 1] + F[i][k] * T[i + k + 1][j - k - 1])
            else:
                T[i][j] += (T[i][k] * T[i + k + 1][j - k - 1] + T[i][k] * F[i + k + 1][j - k - 1] + F[i][k] * T[i + k + 1][j - k - 1])
                F[i][j] += F[i][k] * F[i + k + 1][j - k - 1]
print(T[0][n - 1])
print(F[0][n - 1])
            
