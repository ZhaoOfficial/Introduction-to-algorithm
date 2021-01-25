import numpy as np
import copy

class Matrix:
    def __init__(self, m, n, expr):
        assert isinstance(expr, np.ndarray)

        self.rows, self.cols = m, n
        self.matrix = expr

    def __str__(self) -> str:

        return self.matrix.__str__()

    def __add__(self, other):

        res = self.matrix + other.matrix

        return Matrix(self.rows, self.cols, res)

    def __sub__(self, other):

        res = self.matrix - other.matrix

        return Matrix(self.rows, self.cols, res)

    def __mul__(self, other):

        res = np.zeros((self.rows, self.cols))
        if isinstance(other, Matrix):
            assert self.cols == other.rows
            # # numpy
            res = np.dot(self.matrix, other.matrix)
            result = Matrix(self.rows, other.cols, res)
            
            # # O(n^3)
            # for i in range(self.rows):
            #     for j in range(other.cols):
            #         for k in range(self.cols):
            #             res[i, j] += self.matrix[i, k] * other.matrix[k, j]
            # result = Matrix(self.rows, other.cols, res)

            # # O(n^log7)
            # if self.rows == 1:
            #     return Matrix(1, 1, np.array([[self[0, 0] * other[0, 0]]]))
            # AUpperRow = self.rows // 2
            # ALeftCol = self.cols // 2
            # BUpperRow = other.rows // 2
            # BLeftCol = other.cols // 2

            # A11 = self[0:AUpperRow, 0:ALeftCol]
            # A12 = self[0:AUpperRow, ALeftCol:self.cols]
            # A21 = self[AUpperRow:self.rows, 0:ALeftCol]
            # A22 = self[AUpperRow:self.rows, BLeftCol:self.cols]
            # B11 = other[0:AUpperRow, 0:ALeftCol]
            # B12 = other[0:BUpperRow, BLeftCol:other.cols]
            # B21 = other[BUpperRow:other.rows, 0:BLeftCol]
            # B22 = other[BUpperRow:other.rows, BLeftCol:other.cols]

            # S1 = B12 - B22
            # S2 = A11 + A12
            # S3 = A21 + A22
            # S4 = B21 - B11
            # S5 = A11 + A22
            # S6 = B11 + B22
            # S7 = A12 - A22
            # S8 = B21 + B22
            # S9 = A11 - A21
            # S0 = B11 + B12

            # P1 = A11 * S1
            # P2 = S2 * B22
            # P3 = S3 * B11
            # P4 = A22 * S4
            # P5 = S5 * S6
            # P6 = S7 * S8
            # P7 = S9 * S0

            # C11 = P5 + P4 - P2 + P6
            # C12 = P1 + P2
            # C21 = P3 + P4
            # C22 = P5 + P1 - P3 - P7

            # result = Matrix(self.rows, other.cols, res)
            # result[0:C11.rows, 0:C11.cols] = C11
            # result[0:C11.rows, C11.cols:result.cols] = C12
            # result[C11.rows:result.rows, 0:C21.cols] = C21
            # result[C11.rows:result.rows, C11.cols:result.cols] = C22

            return result
        elif isinstance(other, int) or isinstance(other, float):
            res = self.matrix * other
            return Matrix(self.rows, self.cols, res)

    def __truediv__(self, other):

        res = self.matrix / other

        return Matrix(self.rows, self.cols, res)

    def __eq__(self, other):
        if self.rows != other.rows or self.cols != other.cols:
            return False
        return np.allclose(self.matrix, other.matrix)

    def transpose(self):

        res = self.matrix.T

        return Matrix(self.rows, self.cols, res)

    def det(self):

        return np.linalg.det(self.matrix)

    def inv(self):

        return np.linalg.inv(self.matrix)

    def __getitem__(self, key):

        if isinstance(key, int):
            return Matrix(1, self.cols, np.array([self.matrix[key, :]]))

        elif isinstance(key, tuple):
            row, col = key
            if isinstance(row, int) and isinstance(col, int):
                return self.matrix[key]
            elif isinstance(row, slice) and isinstance(col, slice):
                res = self.matrix[key]
                return Matrix(res.shape[0], res.shape[1], res)

    def __setitem__(self, key, value):
        if isinstance(key, int):
            self.matrix[key] = value.matrix[0]

        elif isinstance(key, tuple):
            row, col = key
            if isinstance(row, int) and isinstance(col, int):
                self.matrix[key] = value
            elif isinstance(row, slice) and isinstance(col, slice):
                self.matrix[key] = value.matrix

    # Self-defined methods
    # Feel free to define your own methods for class Matrix here

import time
size = 512
x = np.ones((size, size))
a = Matrix(size, size, x)
b = Matrix(size, size, x)

start = time.process_time()
print((a * b)[0, 0])
print(time.process_time() - start)

# n         64      128     256     512
# O(n^log7) 1.46    9.72    67.13   463.2
# O(n^3)    0.21    1.86    13.64   116.0   (iterative)
# O(n^3)    0.0     0.0     0.0     0.0     (numpy)