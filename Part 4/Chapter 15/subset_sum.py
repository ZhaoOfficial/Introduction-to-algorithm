import random

number = [random.randint(1, 15) for i in range(50)]
n = len(number)
target = 50

index = []
def subsetSum(number, i, target):
    if target < 0:
        return False
    if target == 0:
        return True
    if i == n:
        return False

    if subsetSum(number, i + 1, target - number[i]):
        index.append(i)
        return True
    return subsetSum(number, i + 1, target)



subsetSum(number, 0, target)
print(index)
print([number[index[i]] for i in range(len(index))])