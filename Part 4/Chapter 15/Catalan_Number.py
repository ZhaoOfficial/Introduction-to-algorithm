import scipy.special

def Catalan_recursion(n):
    Cn = [1]
    yield 1
    for i in range(1, n):
        Ci = 0
        #* compute half of series then double it
        for j in range(i // 2):
            Ci += Cn[j] * Cn[-1 - j]
        Ci *= 2
        #* if odd, add the middle item
        if i % 2 == 1:
            Ci += Cn[i // 2] ** 2

        Cn.append(Ci)
        yield Ci

def Catalan_sequence(n):
    for i in range(1, n + 1):
        yield scipy.special.comb(2 * i - 2, i - 1, exact = True) // i

for i in Catalan_recursion(10):
    print(i, end = ", ")
print()
for i in Catalan_sequence(10):
    print(i, end = ", ")