import random

# O((digit / radix)(n + 2^radix))
def RadixSort(a, RADIX = 10):
    maximum = max(a)
    digit = 1 # RADIX ** 0

    while maximum // digit != 0:
        # declare and initialize buckets
        buckets = [list() for _ in range(RADIX)]

        # split array between lists
        for i in range(len(a)):
            buckets[a[i] // digit % RADIX].append(a[i])

        # move to next digit
        digit *= RADIX

        # empty lists into array
        j = 0
        for r in range(RADIX):
            for i in range(len(buckets[r])):
                a[j] = buckets[r][i]
                j += 1

a = [random.randint(0, 100) for _ in range(50)]
RadixSort(a)
print(a)