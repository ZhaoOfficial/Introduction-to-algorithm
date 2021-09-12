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

def fibonacci_No_Optimization(n:int):
    return 1 if n <= 2 else fibonacci_No_Optimization(n - 1) + fibonacci_No_Optimization(n - 2)


# since the recursive function will call
# the decorator each time we call the function
@duration
def fib_No_Optimization(n):
    return fibonacci_No_Optimization(n)

def fibonacci_Optimization(n, array):
    if (array[n] == 0):
        if n <= 2:
            array[n] = 1
        else:
            array[n] = fibonacci_Optimization(n - 1, array) + fibonacci_Optimization(n - 2, array)
    return array[n]

@duration
def fib_Optimization(n):
    array = [0 for _ in range(n + 1)]
    return fibonacci_Optimization(n, array)

n = 35
# O(2^n)
print(fib_No_Optimization(n))
# O(2n)
print(fib_Optimization(n))