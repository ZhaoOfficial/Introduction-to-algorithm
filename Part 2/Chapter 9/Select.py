def partition(a, low, high):
    pivot = a[high]
    i = low - 1
    for j in range(low, high):
        if a[j] < pivot:
            i += 1
            a[i], a[j] = a[j], a[i]
    a[i + 1], a[high] = a[high], a[i + 1]
    return i + 1

def select(a, low, high, i):
    if low == high:
        return a[low]
    mid = partition(a, low, high)
    k = mid - low
    if i == k:
        return a[high]
    elif i < k:
        return select(a, low, mid - 1, i)
    else:
        return select(a, mid + 1, high, i - k)

a = list(range(0, 100))
b = select(a, 0, len(a) - 1, 15)
print(b)