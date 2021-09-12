def lcs(X, Y):
    m = len(X)
    n = len(Y)
    length = [[0] * (n) for _ in range(m)]
    way = [[""] * (n) for _ in range(m)]

    for i in range(m):
        for j in range(n):
            if X[i] == Y[j]:
                length[i][j] = length[i - 1][j - 1] + 1
                way[i][j] = 's'
            elif length[i - 1][j] >= length[i][j - 1]:
                length[i][j] = length[i - 1][j]
                way[i][j] = 'u'
            else:
                length[i][j] = length[i][j - 1]
                way[i][j] = 'l'
    return length, way

def lcs_way(way, X, i, j):
    if i == -1 or j == -1:
        return
    if way[i][j] == 's':
        lcs_way(way, X, i - 1, j - 1)
        print(X[i], end = "")
    elif way[i][j] == 'u':
        lcs_way(way, X, i - 1, j)
    else:
        lcs_way(way, X, i, j - 1)

X = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA"
Y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA"
length, way = lcs(X, Y)
lcs_way(way, X, len(X) - 1, len(Y) - 1)