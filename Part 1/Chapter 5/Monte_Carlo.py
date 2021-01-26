"""
Using Monte Carlo to get
an approximate value of pi
"""
import numpy as np
import matplotlib.pyplot as plt

n = 20000
x = np.random.random_sample((n, )) * 2 - 1
y = np.random.random_sample((n, )) * 2 - 1
distance = x ** 2 + y ** 2
in_circle_number = np.count_nonzero([distance < 1])
pi = np.sum(in_circle_number) * 4 / n

print("pi =", pi)

index = np.linspace(-1.0, 1.0, num = 10000)
circle = np.sqrt(1 - index ** 2)
in_circle_x = x[distance < 1]
in_circle_y = y[distance < 1]
out_circle_x = x[distance >= 1]
out_circle_y = y[distance >= 1]
plt.figure(figsize = (8, 8))
plt.scatter(in_circle_x, in_circle_y, color = 'gold', marker = '.', linewidths = 1)
plt.scatter(out_circle_x, out_circle_y, color = 'royalblue', marker = '.', linewidths = 1)
plt.plot(index, circle, color = 'crimson')
plt.plot(index, -circle, color = 'crimson')
plt.show()