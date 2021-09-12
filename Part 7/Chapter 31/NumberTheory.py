# -*- coding:utf-8 -*-
import math
import json

class NumberTheory(object):
    """
    Simple but essential implementations
    of some number theory algorithms.
    """

    with open("first_1e6_prime.json", "r") as __f:
        # range(2, 15485864) in prime
        first_1e6_prime = json.load(__f)

    @classmethod
    def gcd(self, a: int, b: int) -> int:
        """
        Euclidean Algorithm.

        @param:
        a, b are integers.

        @return:
        The greatest common divisor of a and b.
        """
        assert isinstance(a, int), "a should be an integer"
        assert isinstance(b, int), "b should be an integer"

        while b != 0:
            c = b
            b = a % b
            a = c

        return a

    @classmethod
    def eea(self, a: int, b: int) -> (int, int):
        """
        Extended Euclidean Algorithm.

        @param:
        a, b are integers.

        @return:
        The gcd(a, b) and the solution (x, y) to the equation ax + by = gcd(a, b).
        Here, x always greater than 0.
        """
        assert isinstance(a, int), "a should be an integer"
        assert isinstance(b, int), "b should be an integer"

        a0, b0 = a, b
        x0, y0 = 1, 0
        x1, y1 = 0, 1
        s, t = 0, 0

        while b != 0:
            q, r = divmod(a, b)
            s, t = x1, y1
            x1, y1 = x0 - q * x1, y0 - q * y1
            x0, y0 = s, t
            c = b
            b = r
            a = c

        while x0 < 0:
            x0 += b0
            y0 -= a0

        return a, x0, y0

    @classmethod
    def square_and_multiply(self, a: int, b: int, m: int) -> int:
        """
        Square and multiply method for a ** b % m.
        In Python, it is pow(a, b, m).

        @param:
        a, b, m are integers.

        @return:
        The value of a ** b % m.
        """

        binary = bin(b)[3:]

        result = a
        for i in binary:
            result *= result
            result %= m
            if i == "1":
                result *= a
                result %= m

        return result

    @classmethod
    def is_prime(self, n: int) -> bool:
        """
        Judge whether a number is prime or not.

        @param:
        n is a positive integer.

        @return:
        A boolean value.
        """
        assert isinstance(n, int) and n >= 2, "n is an integer greater than 1"

        s = math.sqrt(n)
        for p in self.first_1e6_prime:
            if p <= s and n % p == 0:
                return False

        while p <= s:
            p += 2
            if n % p == 0:
                return False

        return True

    @classmethod
    def Miller_Rabin(self, n: int) -> bool:
        """
        Miller-Rabin prime test.

        @param:
        n is a positive integer.

        @return:
        If n is prime, return True.
        """
        #TODO::
        pass


    @classmethod
    def factor(self, n: int) -> list:
        """
        Prime factorizations of an integer greater than 1.

        @param:
        n is an integer greater than 1.

        @return:
        A list of prime whose product is n in ascending order.
        """

        assert isinstance(n, int) and n >= 2, "n is an integer greater than 1"

        result = []
        s = math.ceil(math.sqrt(n))

        # if it can be factored in first_1e6_prime
        for p in self.first_1e6_prime:
            while p <= s and n % p == 0:
                n //= p
                s = math.ceil(math.sqrt(n))
                result.append(p)
            if n == 1:
                break

        # if it can not
        while p <= s:
            p += 2
            while n % p == 0:
                n //= p
                s = math.ceil(math.sqrt(n))
                result.append(p)
            if n == 1:
                break
        else:
            result.append(n)

        return result

    @classmethod
    def phi(self, n: int) -> int:
        """
        The number of the numbers that are relatively prime to n.

        @param:
        n is a positive integer.

        @return:
        The number of the results that are relatively prime to n.
        """

        assert isinstance(n, int) and n > 0, "n must be a positive integer"

        if n == 1:
            return 1

        factors = self.factor(n)

        primes = [factors[0]]
        for p in factors:
            if p != primes[-1]:
                primes.append(p)

        result = n
        for p in primes:
            result //= p
            result *= (p - 1)

        return result

    @classmethod
    def sigma(self, n: int) -> int:
        """
        The sum of all the divisor of n.

        @param:
        n is a positive integer.

        @return:
        The sum of all the divisor of n.
        """

        assert isinstance(n, int) and n > 0, "n must be a positive integer"

        if n == 1:
            return 1

        factors = self.factor(n)

        primes = [[factors[0], 0]]
        for p in factors:
            if p != primes[-1][0]:
                primes.append([p, 1])
            else:
                primes[-1][1] += 1

        result = 1
        for p, e in primes:
            result *= (p ** (e + 1) - 1)
            result //= (p - 1)

        return result


class Problem(object):
    """
    Some solutions to some problems.
    """

    @classmethod
    def triplet_eea(self, a: int, b: int, c: int) -> (int, int, int):
        """
        Solve the equation ax + by + cz = 1.

        @param:
        a, b, c are non negative integer.

        @return:
        The solution (x, y, z) to the equation ax + by + cz = 1.
        """

        assert isinstance(a, int), "a should be a non negative integer"
        assert isinstance(b, int), "b should be a non negative integer"
        assert isinstance(c, int), "c should be a non negative integer"

        d = NumberTheory.gcd(a, b)
        if d == 0:
            if c != 1:
                print("No solution to {}x + {}y + {}z = 1.".format(a, b, c))
                return None
            else:
                return (0, 0, 1)
        if NumberTheory.gcd(d, c) != 1:
            print("No solution to {}x + {}y + {}z = 1.".format(a, b, c))
            return None

        _, u, z = NumberTheory.eea(d, c)
        n = (1 - c * z) // d
        _, x, y = NumberTheory.eea(a, b)

        return n * x, n * y, z

    @classmethod
    def solve_linear_congruence(self, a: int, b: int, m: int) -> int:
        """
        Solve the linear congruence ax == b (mod m).

        @param:
        a, c, m are integers for ax == b (mod m)

        @return:
        All incongruent solutions to ax == b (mod m) with length gcd(a, m).
        The special solution is the first element of the return list.
        """
        g, x, y = NumberTheory.eea(a, m)
        result = []
        if b % g == 0:
            x0 = (x * b // g) % m
            for k in range(g):
                result.append((x0 + k * m // g) % m)
        else:
            print("No solution to {}x == {} (mod {}).".format(a, b, m))
        return result

    @classmethod
    def Chinese_remainder_theorem(self, pairs: list) -> int:
        """
        Solve the linear congruence equations x == ri (mod ni) ...

        @param:
        A list contains pairs of remainders and modulus.

        @return:
        The smallest positive solution to the linear congruence equations.
        """

        N = 1
        for ri, ni in pairs:
            N *= ni

        result = 0
        for ri, ni in pairs:
            Ni = N // ni
            g, si, ti = NumberTheory.eea(Ni, ni)
            result += si * Ni * ri
        return result % N


import time
if __name__ == "__main__":
    pass
    # print(NumberTheory.gcd(36,48))
    # print(NumberTheory.gcd(0,48))
    # print(NumberTheory.gcd(36,0))
    # print(NumberTheory.gcd(0,0))

    # print(NumberTheory.eea(60, 0))
    # print(NumberTheory.eea(22, 60))
    # print(NumberTheory.eea(12453, 2347))
    # print(NumberTheory.eea(12345, 67890))
    # print(NumberTheory.eea(54321, 9876))

    # print(NumberTheory.square_and_multiply(2, 3, 5))
    # print(NumberTheory.square_and_multiply(3, 2, 5))
    # print(NumberTheory.square_and_multiply(40, 17, 55))
    # print(NumberTheory.square_and_multiply(257, 2872, 49))

    # print(NumberTheory.is_prime(2))
    # print(NumberTheory.is_prime(15485863))
    # print(NumberTheory.is_prime(15485864))
    # print(NumberTheory.is_prime(15485863 * 15485863 + 10000000000))

    # print(NumberTheory.factor(2))
    # print(NumberTheory.factor(15485863))
    # print(NumberTheory.factor(15485864))
    # print(NumberTheory.factor(15485863 * 15485863 + 10000000000))

    # print(NumberTheory.phi(97))
    # print(NumberTheory.phi(2401))
    # print(NumberTheory.phi(8800))
    # print(NumberTheory.phi(15485863 * 15485863 + 10000000000))

    # print(NumberTheory.sigma(10))
    # print(NumberTheory.sigma(20))
    # print(NumberTheory.sigma(1728))

    # print(Problem.triplet_eea(155, 341, 385))
    # print(Problem.triplet_eea(50, 30, 40))
    # print(Problem.triplet_eea(0, 0, 0))

    # print(Problem.solve_linear_congruence(943, 381, 2576))
    # print(Problem.solve_linear_congruence(7, 3, 15))
    # print(Problem.solve_linear_congruence(72, 47, 200))
    # print(Problem.solve_linear_congruence(4183, 5781, 15087))

    # print(Problem.Chinese_remainder_theorem([[3, 7], [5, 9]]))
    # print(Problem.Chinese_remainder_theorem([[3, 37], [1, 87]]))
    # print(Problem.Chinese_remainder_theorem([[5, 7], [2, 12], [8, 13]]))
    # print(Problem.Chinese_remainder_theorem([[2, 3], [3, 5], [2, 7]]))
    # print(Problem.Chinese_remainder_theorem([[1, 60], [0, 7]]))



    # t = time.time()
    # print(time.time() - t)