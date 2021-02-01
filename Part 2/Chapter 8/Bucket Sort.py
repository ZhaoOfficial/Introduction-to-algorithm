import random

def BucketSort(a):
    maximum = max(a) + 1
    buckets = [list() for _ in range(10)]

    for elem in a:
        buckets[elem * 10 // maximum].append(elem)
    
    for bucket in buckets:
        bucket.sort()
    
    b = []
    for bucket in buckets:
        b.extend(bucket)
    
    return b

a = [random.randint(0, 100) for _ in range(50)]
a = BucketSort(a)
print(a)