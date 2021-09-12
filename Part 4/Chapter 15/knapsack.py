# 0 - 1 package

n = 5
Max_weight = 11
value = [0, 1, 6, 18, 22, 28]
weight = [0, 1, 2, 5, 6, 7]

def package(n, upperWeight):
    if n == 0:
        return 0
    if weight[n] > upperWeight:
        return package(n - 1, upperWeight)
    return max(package(n - 1, upperWeight), value[n] + package(n - 1, upperWeight - weight[n]))

print(package(5, Max_weight))

    