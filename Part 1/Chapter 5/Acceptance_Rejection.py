"""
Using acceptance rejection to implement
Normal distribution
"""
import numpy as np
import matplotlib.pyplot as plt

n = 10000

# g(x) = e^{-x}
# Y ~ Expo(1)
U1 = np.random.random_sample((n, ))
Y = -np.log(U1)

# c = \sup\frac{f(x)}{g(x)}
c = np.sqrt(2 * np.e / np.pi)
# \frac{f(x)}{cg(x)} = e^{-0.5(x - 1)^2}

U2 = np.random.random_sample((n, ))
X = Y[U2 <= np.exp(-0.5 * (Y - 1) ** 2)]

U3 = np.random.random_sample((len(X), ))
sign = np.where(U3 > 0.5, 1, -1)
X = sign * X


plt.figure(figsize = (10, 8))
plt.xlim((-4, 4))
plt.hist(X, bins = 100, color = 'r', alpha = 0.4, edgecolor = 'y', label = 'sample')
plt.show()