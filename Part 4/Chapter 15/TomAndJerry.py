card = [1, 2, 5, 9, 8, 7, 6, 3, 2, 5, 4]
n = len(card)

def TAJ(card, l, r):
    if r - l < 1:
        return 0

    if card[l] < card[r]:
        return max(TAJ(card, l + 1, r - 1) + card[l], TAJ(card, l, r - 2) + card[r - 1])
    elif card[l] == card[r]:
        return max(TAJ(card, l + 1, r - 1) + card[l], TAJ(card, l, r - 2) + card[r - 1], TAJ(card, l + 1, r - 1) + card[r], TAJ(card, l + 2, r) + card[l + 1])
    else:
        return max(TAJ(card, l + 1, r - 1) + card[r], TAJ(card, l + 2, r) + card[l + 1])
print(TAJ(card, 0, len(card) - 1))

dp = [[0 for _ in range(n)] for __ in range(n)]

for l in range(n - 1, -1, -1):
    for r in range(l + 1, n, 1):
        if r - l == 1:
            dp[l][r] = min(card[l], card[r])
            continue
        if card[l] > card[r]:
            dp[l][r] = max(dp[l + 1][r - 1] + card[r], dp[l + 2][r] + card[l + 1])
        else:
            dp[l][r] = max(dp[l + 1][r - 1] + card[l], dp[l][r - 2] + card[r - 1])
print(dp[0][n - 1])
