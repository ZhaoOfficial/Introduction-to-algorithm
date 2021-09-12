# Paint a row of n houses red, green, or blue so that
# No two adjacent houses have the same color.
# Minimize total cost, where cost(i, color) is cost to paint i given color

n = 6

red = [0, 7, 6, 7, 8, 9, 20]
green = [0, 3, 8, 9, 22, 12, 8]
blue = [0, 16, 10, 4, 2, 5, 7]

cost = [red, green, blue]
total = [[0] * (n + 1) for j in range(3)]

print(cost)
for j in range(1, n + 1):
    for i in range(3):
        total[i][j] = cost[i][j] + min(total[(i - 1) % 3][j - 1], total[(i + 1) % 3][j - 1])

print(total)
print(min(total[0][n], total[1][n], total[2][n]))