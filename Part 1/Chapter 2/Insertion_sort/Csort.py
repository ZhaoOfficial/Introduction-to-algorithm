a = ['Place Holder', 5, 8, 9, 6, 7, 2, 3, 1, 4]
for i in range(1, len(a) - 1):
    minimal = i
    j = i
    while j < len(a):
        if a[j] < a[minimal]:
            minimal = j
        j += 1
    a[minimal], a[i] = a[i], a[minimal]
print(a)