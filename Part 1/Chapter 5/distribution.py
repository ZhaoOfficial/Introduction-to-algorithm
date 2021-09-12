"""
Named distribution learned in
Probability and Statistics
"""
import numpy as np
import matplotlib.pyplot as plt
import scipy.special

#! <<<---------- Discrete ---------->>>
class Discrete(object):

    @staticmethod
    def Bern(p) -> bool:
        assert 0 <= p <= 1, 'p should be in [0, 1].'

        return np.random.random_sample() < p

    @staticmethod
    def Bin(n, p) -> int:
        assert 0 <= p <= 1, 'p should be in [0, 1].'
        
        total = 0
        for _ in range(n):
            total += Discrete.Bern(p)

        return total

    @staticmethod
    def Geom(p) -> int:
        assert 0 <= p <= 1, 'p should be in [0, 1].'
        
        total = 0
        while Discrete.Bern(p) is False:
            total += 1

        return total

    @staticmethod
    def FS(p) -> int:
        assert 0 <= p <= 1, 'p should be in [0, 1].'
        
        return Discrete.Geom(p) + 1

    @staticmethod
    def NBin(r, p) -> int:
        assert 0 <= p <= 1, 'p should be in [0, 1].'
        assert isinstance(r, int) and r > 0, 'r should be positive integer.'

        total = 0
        for _ in range(r):
            total += Discrete.Geom(p)

        return total

    @staticmethod
    def HGeom(w, b, n):
        assert w >= 0, 'w should be non negative.'
        assert b >= 0, 'b should be non negative.'
        assert w + b >= n, 'n should be no more than w + b.'

        localW = w
        localB = b
        total = 0

        for _ in range(n):
            if Discrete.Bern(localW / (localW + localB)) == True:
                total += 1
                localW -= 1
            else:
                localB -= 1

        return total

    @staticmethod
    def Pois(L) -> int:
        assert L > 0, 'L should be greater than 0.'

        t = 1
        temp = Continuous.Expo(L)
        total = 0
        while temp < t:
            temp += Continuous.Expo(L)
            total += 1
        
        return total

    @staticmethod
    def draw(index, pmf, cdf, theoreticalPMF, theoreticalCDF, *args):

        outString = args[0] + '('
        for i in range(1, len(args) - 1):
            outString += str(args[i]) + ', '
        outString += str(args[-1]) + ')'

        plt.figure(figsize = (12, 8))
        plt.subplot(1, 2, 1)
        plt.bar(index, pmf, color = 'yellowgreen', label = 'pmf')
        plt.plot(index, theoreticalPMF, color = 'indianred', label = 'theoreticalPMF')
        plt.title('PMF of ' + outString)
        plt.legend(bbox_to_anchor = (-0.1, 1.1), loc = 'upper left')

        plt.subplot(1, 2, 2)
        plt.bar(index, cdf, color = 'yellowgreen', label = 'cdf')
        plt.plot(index, theoreticalCDF, color = 'indianred', label = 'theoreticalCDF')
        plt.title('CDF of ' + outString)
        plt.legend(bbox_to_anchor = (-0.1, 1.1), loc = 'upper left')
        plt.show()

#! <<<---------- Continuous ---------->>>
class Continuous(object):

    @staticmethod
    def Unif(a, b) -> float:
        assert a <= b, 'a should be no greater than b'

        return (b - a) * np.random.random_sample() + a

    @staticmethod
    def Expo(L) -> float:
        assert L > 0, 'L should be greater than 0.'

        return -(np.log(Continuous.Unif(0, 1)) / L)

    @staticmethod
    def Normal(mu, sigma) -> float:
        assert sigma >= 0, 'sigma should be no less than 0'
        
        X = Continuous.Unif(0, 1)
        Y = Continuous.Unif(0, 2 * np.pi)
        Z = np.sqrt(-2 * np.log(X)) * np.sin(Y) * sigma + mu

        return Z

    @staticmethod
    def Beta(a, b) -> float:
        assert a > 0, 'a should be greater than 0'
        assert b > 0, 'b should be greater than 0'

        X1 = Continuous.Gamma(a, 1)
        X2 = Continuous.Gamma(b, 1)
        
        Y = X1 / (X1 + X2)
        return Y

    @staticmethod
    def Gamma(a, L) -> float:
        assert a > 0, 'a should be greater than 0'
        assert L > 0, 'L should be greater than 0'

        # i.i.d Expo(L) is restrictive 
        # since "a" may not be an integer
        
        integer = int(a)
        total = 0
        for _ in range(integer):
            total += Continuous.Expo(L)
        a -= integer
        if a == 0:
            return total
        y = 0

        b = 1 + a / np.e
        while True:
            U = Continuous.Unif(0, 1)
            P = Continuous.Unif(0, b)
            
            if P > 1:
                y = -np.log((b - P) / a)
                if U < np.power(y, a - 1):
                    return y * L + total
            else:
                y = np.power(P, 1 / a)
                if U < np.exp(-y):
                    return y * L + total

    @staticmethod
    def draw(index, binNumber, generated_data, theoreticalPDF, theoreticalCDF, *args):

        outString = args[0] + '('
        for i in range(1, len(args) - 1):
            outString += str(args[i]) + ', '
        outString += str(args[-1]) + ')'

        plt.figure(figsize = (12, 8))
        plt.subplot(2, 2, (1, 3))
        plt.hist(generated_data, bins = binNumber, color = 'r', alpha = 0.4, edgecolor = 'y', label = 'sample')
        plt.title('Sample of ' + outString)
        plt.legend(bbox_to_anchor = (-0.1, 1.1), loc = 'upper left')

        plt.subplot(2, 2, 2)
        plt.plot(index, theoreticalPDF, color = 'indigo', label = 'PDF')
        plt.title('PDF of ' + outString)
        plt.legend(bbox_to_anchor = (1.1, 1.15), loc = 'upper right')

        plt.subplot(2, 2, 4)
        plt.plot(index, theoreticalCDF, color = 'lightseagreen', label = 'CDF')
        plt.title('CDF of ' + outString)
        plt.legend(bbox_to_anchor = (1.1, 1.15), loc = 'upper right')
        plt.show()


if __name__ == "__main__":

    time = 10000
    binNumber = 500

    #! <<<---------- Bern ---------->>>
    p = 0.3
    generated_data = np.asarray([Discrete.Bern(p) for _ in range(time)])

    index = np.arange(0, 2, dtype = float)
    pmf = np.asarray([np.sum(generated_data == False), np.sum(generated_data == True)])
    cdf = np.cumsum(pmf)
    theoreticalPMF = np.asarray([(1 - p) * time, p * time])
    theoreticalCDF = np.cumsum(theoreticalPMF)

    Discrete.draw(index, pmf, cdf, theoreticalPMF, theoreticalCDF, 'Bern', p)

    #! <<<---------- Bin ---------->>>
    p = 0.4
    n = 20
    generated_data = np.asarray([Discrete.Bin(n, p) for _ in range(time)])
    index = np.arange(0, n + 1, dtype = float)

    pmf = np.asarray([np.sum(generated_data == index[i]) for i in range(n + 1)])
    cdf = np.cumsum(pmf)
    theoreticalPMF = scipy.special.comb(n, index) * p ** index * (1 - p) ** (n - index) * time
    theoreticalCDF = np.cumsum(theoreticalPMF)
    
    Discrete.draw(index, pmf, cdf, theoreticalPMF, theoreticalCDF, 'Bin', n, p)

    #! <<<---------- Geom ---------->>>
    p = 0.5
    generated_data = np.asarray([Discrete.Geom(p) for _ in range(time)])
    n = np.max(generated_data)
    index = np.arange(0, n + 1, dtype = float)

    pmf = np.asarray([np.sum(generated_data == index[i]) for i in range(n + 1)])
    cdf = np.cumsum(pmf)
    theoreticalPMF = (1 - p) ** index * p * time
    theoreticalCDF = np.cumsum(theoreticalPMF)
    
    Discrete.draw(index, pmf, cdf, theoreticalPMF, theoreticalCDF, 'Geom', p)

    #! <<<---------- FS ---------->>>
    p = 0.1
    generated_data = np.asarray([Discrete.FS(p) for _ in range(time)])
    n = np.max(generated_data)
    index = np.arange(1, n + 1, dtype = float)

    pmf = np.asarray([np.sum(generated_data == index[i - 1]) for i in range(1, n + 1)])
    cdf = np.cumsum(pmf)
    theoreticalPMF = (1 - p) ** (index - 1) * p * time
    theoreticalCDF = np.cumsum(theoreticalPMF)
    
    Discrete.draw(index, pmf, cdf, theoreticalPMF, theoreticalCDF, 'FS', p)

    #! <<<---------- NBin ---------->>>
    p = 0.2
    r = 10
    generated_data = np.asarray([Discrete.NBin(r, p) for _ in range(time)])
    n = np.max(generated_data)
    index = np.arange(1, n + 1, dtype = float)

    pmf = np.asarray([np.sum(generated_data == index[i - 1]) for i in range(1, n + 1)])
    cdf = np.cumsum(pmf)
    theoreticalPMF = scipy.special.comb(index + r - 1, r - 1) * (1 - p) ** index * p ** r * time
    theoreticalCDF = np.cumsum(theoreticalPMF)
    
    Discrete.draw(index, pmf, cdf, theoreticalPMF, theoreticalCDF, 'NBin', r, p)

    #! <<<---------- HGeom ---------->>>
    w = 30
    b = 30
    n = 20
    generated_data = np.asarray([Discrete.HGeom(w, b, n) for _ in range(time)])
    index = np.arange(0, n + 1, dtype = float)

    pmf = np.asarray([np.sum(generated_data == index[i]) for i in range(n + 1)])
    cdf = np.cumsum(pmf)
    theoreticalPMF = scipy.special.comb(w, index) * scipy.special.comb(b, n - index) / scipy.special.comb(w + b, n) * time
    theoreticalCDF = np.cumsum(theoreticalPMF)
    
    Discrete.draw(index, pmf, cdf, theoreticalPMF, theoreticalCDF, 'HGeom', w, b, n)

    #! <<<---------- Pois ---------->>>
    L = 100
    generated_data = np.asarray([Discrete.Pois(L) for _ in range(time)])
    n = np.max(generated_data)
    index = np.arange(0, n + 1, dtype = float)

    pmf = np.asarray([np.sum(generated_data == index[i]) for i in range(n + 1)])
    cdf = np.cumsum(pmf)
    theoreticalPMF = np.exp(-L) * L ** index / scipy.special.factorial(index) * time
    theoreticalCDF = np.cumsum(theoreticalPMF)
    
    Discrete.draw(index, pmf, cdf, theoreticalPMF, theoreticalCDF, 'Pois', L)

    #! <<<---------- Unif ---------->>>
    a = 0
    b = 5
    generated_data = np.asarray([Continuous.Unif(a, b) for _ in range(time)])
    n = np.max(generated_data)
    index = np.linspace(a, b, binNumber)

    generated_data = np.sort(generated_data)
    theoreticalPDF = np.ones((binNumber, )) * (1 / (b - a))
    theoreticalCDF = (index - a) / (b - a)

    Continuous.draw(index, binNumber, generated_data, theoreticalPDF, theoreticalCDF, 'Unif', a, b)

    #! <<<---------- Expo ---------->>>
    L = 1
    generated_data = np.asarray([Continuous.Expo(L) for _ in range(time)])
    n = np.max(generated_data)
    index = np.linspace(0, n, binNumber)

    pdf = np.sort(generated_data)
    cdf = np.cumsum(pdf)
    theoreticalPDF = L * np.exp(- L * index)
    theoreticalCDF = 1 - np.exp(- L * index)

    Continuous.draw(index, binNumber, generated_data, theoreticalPDF, theoreticalCDF, 'Expo', L)

    #! <<<---------- Normal ---------->>>
    mu = 3
    sigma = 10
    generated_data = np.asarray([Continuous.Normal(mu, sigma) for _ in range(time)])
    m = np.min(generated_data)
    n = np.max(generated_data)
    index = np.linspace(m, n, binNumber)

    pdf = np.sort(generated_data)
    cdf = np.cumsum(pdf)
    theoreticalPDF = (1 / np.sqrt(2 * np.pi * sigma ** 2)) * np.exp(-(index - mu) ** 2 / (2 * sigma ** 2))
    temp = np.cumsum(theoreticalPDF)
    theoreticalCDF = temp / temp[-1]

    Continuous.draw(index, binNumber, generated_data, theoreticalPDF, theoreticalCDF, 'Normal', mu, sigma)

    #! <<<---------- Beta ---------->>>
    a = 0.5
    b = 2
    generated_data = np.asarray([Continuous.Beta(a, b) for _ in range(time)])
    index = np.linspace(0, 1, binNumber)[1:-1]

    pdf = np.sort(generated_data)
    cdf = np.cumsum(pdf)
    theoreticalPDF = index ** (a - 1) * (1 - index) ** (b - 1) / scipy.special.beta(a, b)
    temp = np.cumsum(theoreticalPDF)
    theoreticalCDF = temp / temp[-1]

    Continuous.draw(index, binNumber, generated_data, theoreticalPDF, theoreticalCDF, 'Beta', a, b)

    #! <<<---------- Gamma ---------->>>
    a = 5.5
    L = 1
    generated_data = np.asarray([Continuous.Gamma(a, L) for _ in range(time)])
    n = np.max(generated_data)
    index = np.linspace(0, n, binNumber)[1:]

    pdf = np.sort(generated_data)
    cdf = np.cumsum(pdf)
    theoreticalPDF = (L * index) ** a * np.exp(-L * index) / index / scipy.special.gamma(a)
    temp = np.cumsum(theoreticalPDF)
    theoreticalCDF = temp / temp[-1]

    Continuous.draw(index, binNumber, generated_data, theoreticalPDF, theoreticalCDF, 'Gamma', a, L)
    