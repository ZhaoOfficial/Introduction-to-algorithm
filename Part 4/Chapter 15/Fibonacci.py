def duration(fn): 
    # print("fn 1: {}".format(fn))
    def inner(arg):
        import time

        start = time.time()
        result = fn(arg)
        end = time.time()
        print("time: " + str(end - start) + 's')
        return result
    return inner

def fibonacci_No_Optimal(n:int):
    return 1 if n <= 2 else fibonacci_No_Optimal(n - 1) + fibonacci_No_Optimal(n - 2)


# since the recursive function will call
# the decorator each time we call the function
@duration
def fib_No_Optimal(n):
    return fibonacci_No_Optimal(n)

def fibonacci_Optimal(n, array):
    if (array[n] == 0):
        if n <= 2:
            array[n] = 1
        else:
            array[n] = fibonacci_Optimal(n - 1, array) + fibonacci_Optimal(n - 2, array)
    return array[n]

@duration
def fib_Optimal(n):
    array = [0 for _ in range(n + 1)]
    return fibonacci_Optimal(n, array)

n = 35
# O(2^n)
print(fib_No_Optimal(n))
# O(2n)
print(fib_Optimal(n))