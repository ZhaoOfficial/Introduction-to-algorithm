# -*- coding:utf-8 -*-
from NumberTheory import NumberTheory

class Rationale(object):
    def __init__(self, numerator, denominator):

        assert denominator != 0

        g = NumberTheory.gcd(numerator, denominator)
        numerator //= g
        denominator //= g

        self.numerator = numerator
        self.denominator = denominator

    def __add__(self, other):

        if isinstance(other, Rationale):
            numerator = self.numerator * other.denominator + other.numerator * self.denominator
            denominator = self.denominator * other.denominator
        elif isinstance(other, int):
            return self + Rationale(other, 1)
        else:
            raise TypeError("{} is not a Rationale or an integer.".format(other))

        return Rationale(numerator, denominator)

    def __sub__(self, other):

        if isinstance(other, Rationale):
            numerator = self.numerator * other.denominator - other.numerator * self.denominator
            denominator = self.denominator * other.denominator
        elif isinstance(other, int):
            return self - Rationale(other, 1)
        else:
            raise TypeError("{} is not a Rationale or an integer.".format(other))

        return Rationale(numerator, denominator)

    def __mul__(self, other):
        
        if isinstance(other, Rationale):
            numerator = self.numerator * other.numerator
            denominator = self.denominator * other.denominator
        elif isinstance(other, int):
            return self * Rationale(other, 1)
        else:
            raise TypeError("{} is not a Rationale or an integer.".format(other))

        return Rationale(numerator, denominator)

    def __truediv__(self, other):

        if isinstance(other, Rationale):
            numerator = self.numerator * other.denominator
            denominator = self.denominator * other.numerator
        elif isinstance(other, int):
            return self / Rationale(other, 1)
        else:
            raise TypeError("{} is not a Rationale or an integer.".format(other))

        return Rationale(numerator, denominator)

    def reciprocal(self):
        return Rationale(self.denominator, self.numerator)

    def __str__(self):
        return str(self.numerator) + ' / ' + str(self.denominator)

if __name__ == '__main__':
    a = Rationale(3, 2)
    b = Rationale(5, 4)
    print(a + b)
    print(a - b)
    print(a * b)
    print(a / b)
    print(a + 2)
    print(a - 2)
    print(a * 2)
    print(a / 2)
    print(a.reciprocal())