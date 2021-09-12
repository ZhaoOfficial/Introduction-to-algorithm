string = "***" * 3
n = len(string)

# def tenet(string, start, end):
#     if start == end:
#         return 1

#     if start > end:
#         return 0

#     if string[start] == string[end]:
#         return tenet(string, start + 1, end - 1) + 2
#     else:
#         return max(tenet(string, start + 1, end), tenet(string, start, end - 1))

# print(tenet(string, 0, n - 1))


dp = [[0 for _ in range(n)] for __ in range(n)]
for i in range(n):
    dp[i][i] = 1

for i in range(1, n, 1):
    for j in range(0, n - i, 1):
        if string[j] == string[j + i]:
            dp[j][j + i] = dp[j + 1][j + i - 1] + 2
        else:
            dp[j][j + i] = max(dp[j + 1][j + i], dp[j][j + i - 1])


print(dp[0][n - 1])
# print(dp)