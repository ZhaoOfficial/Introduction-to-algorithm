## Feel free to import handy built-in modules here
import copy
## Self-defined exceptions
## Please **DO NOT MODIFITY** the following exceptions!
class MatrixKeyError(Exception):
    pass

class MatrixValueError(Exception):
    pass

class MatrixSizeError(Exception):
    pass

class ObjectError(Exception):
    pass

class SizeUnmatchedError(Exception):
    pass

class ScalarTypeError(Exception):
    pass

class NotSquaredError(Exception):
    pass

class NotInvertibleError(Exception):
    pass

class IndexSyntaxError(Exception):
    pass

## Feel free to define your own functions here

## Your implementations start here
class Matrix:
    def __init__(self, m, n, expr):
        '''
        Task 2.1: Load the Matrix in
        Input:
            m: postive integer
            n: postive integer
            expr: string
        Output:
            No output for this task
        '''
        if isinstance(expr, list):
            self.rows, self.cols = m, n
            self.matrix = expr

    def __str__(self) -> str:
        '''
        Task 2.2: Print out the Matrix
        Input:
            No input for this task
        Output:
            expr: string
        '''
        self.output = '['
        for row in self.matrix:
            for elem in row:
                if isinstance(elem, float):
                    self.output += str("%.5f" % elem) + ','
                else:
                    self.output += str(elem) + ','
            self.output = self.output[0:-1] + ';'
        self.output = self.output[0:-1] + ']'

        return self.output

    def __add__(self, other):
        '''
        Task 3.1: Matrix Addition and Subtraction
        Input:
            other: class Matrix
        Output:
            res: class Matrix
        '''
        if not isinstance(other, Matrix):
            raise ObjectError
        if self.rows != other.rows or self.cols != other.cols:
            raise SizeUnmatchedError

        res = [[self.matrix[i][j] + other.matrix[i][j] for j in range(self.cols)] for i in range (self.rows)]

        return Matrix(self.rows, self.cols, res)

    def __sub__(self, other):
        '''
        Task 3.1: Matrix Addition and Subtraction
        Input:
            other: class Matrix
        Output:
            res: class Matrix
        '''
        if not isinstance(other, Matrix):
            raise ObjectError
        if self.rows != other.rows or self.cols != other.cols:
            raise SizeUnmatchedError

        res = [[self.matrix[i][j] - other.matrix[i][j] for j in range(self.cols)] for i in range (self.rows)]

        return Matrix(self.rows, self.cols, res)

    def __mul__(self, other):
        '''
        Task 3.2: Matrix Multiplication
        Input:
            other: class Matrix or scalar (int or float)
        Output:
            res: class Matrix
        '''
        res = [[0 for x in range(self.cols)] for y in range (self.rows)]
        if isinstance(other, Matrix):
            if self.cols != other.rows:
                raise SizeUnmatchedError
            # O(n^3)
            for i in range(self.rows):
                for j in range(other.cols):
                    for k in range(self.cols):
                        res[i][j] += self.matrix[i][k] * other.matrix[k][j]
            result = Matrix(self.rows, other.cols, res)

            # O(n^log7)
            # if self.rows == 1:
            #     return Matrix(1, 1, [[self[0, 0] * other[0, 0]]])
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
            res = [[self.matrix[i][j] * other for j in range(self.cols)] for i in range (self.rows)]
            return Matrix(self.rows, self.cols, res)
        else:
            raise ObjectError

    def __truediv__(self, other):
        '''
        Task 3.3: Matrix Scalar Division
        Input:
            other: scalar (int or float)
        Output:
            res: class Matrix
        '''
        if isinstance(other, int) or isinstance(other, float):
            res = [[self.matrix[i][j] / other for j in range(self.cols)] for i in range (self.rows)]
        else:
            raise ObjectError

        return Matrix(self.rows, self.cols, res)

    def __eq__(self, other):
        '''
        Task 3.4: Matrix Equalization
        Input:
            other: class Matrix
        Output:
            isEqual: bool
        '''
        if not isinstance(other, Matrix):
            raise ObjectError
        if self.rows != other.rows or self.cols != other.cols:
            return False
        for i in range(self.rows):
            for j in range(self.cols):
                if self.matrix[i][j] != other.matrix[i][j]:
                    return False
        return True

    def transpose(self):
        '''
        Task 3.4: Matrix Transpose
        Input:
            No input for this task
        Output:
            res: class Matrix
        '''
        res = [[self.matrix[j][i] for j in range(self.cols)] for i in range (self.rows)]

        return Matrix(self.rows, self.cols, res)

    def det(self):
        '''
        Task 4.1: Matrix Determinant
        Input:
            No input for this task
        Output:
            det: float
        '''
        if self.rows != self.cols:
            raise NotSquaredError

        result = 0
        if self.rows == 1:
            return self.matrix[0][0]
        else:
            for j in range(self.rows):
                result += (-1)**j * self.matrix[0][j] * self.__com(0, j)

        return result

    def inv(self):
        '''
        Task 4.1: Matrix Determinant
        Input:
            No input for this task
        Output:
            mat_inv: class Matrix
        '''

        if self.rows != self.cols:
            raise NotSquaredError
        if self.det() == 0:
            raise NotInvertibleError

        if self.rows == self.cols == 1:
            return Matrix(1, 1, [[1 / self.matrix[0][0]]])

        adj = Matrix(self.rows, self.cols, [[(-1)**(i + j) * self.__com(i, j) for j in range(self.cols)] for i in range(self.rows)]).transpose()
        return adj / self.det()
    
    def __com(self, i, j):
        complement = copy.deepcopy(self.matrix)
        
        complement.pop(i)
        for m in range(len(complement)):
            complement[m].pop(j)
        
        return Matrix(self.rows - 1, self.cols - 1, complement).det()

    def __getitem__(self, key):
        '''
        Task 5: Matrix Indexing
        Input:
            key: integer or tuple
        Output:
            value: scalar (int or float) or class Matrix
        '''

        if isinstance(key, int):
            try:
                return Matrix(1, self.cols, [self.matrix[key]])
            except:
                raise IndexSyntaxError
        elif isinstance(key, tuple):
            if len(key) != 2:
                raise IndexSyntaxError

            row, col = key
            if isinstance(row, int) and isinstance(col, int):
                try:
                    return self.matrix[row][col]
                except:
                    raise IndexSyntaxError
            elif isinstance(row, slice) and isinstance(col, slice):
                try:
                    res = [row[col] for row in self.matrix[row]]
                    return Matrix(len(res), len(res[0]), res)
                except:
                    raise IndexSyntaxError
            else:
                raise MatrixValueError
        else:
            raise IndexSyntaxError

    def __setitem__(self, key, value):
        '''
        Task 5: Matrix Indexing
        Input:
            key: integer or tuple
            value: scalar (int or float) or class Matrix
        Output:
            No output for this task
        '''
        if not isinstance(value, (int, float, Matrix)):
            raise MatrixValueError
        if isinstance(key, int):
            try:
                if not isinstance(value, Matrix):
                    raise ValueError
                if self.cols != value.cols:
                    raise IndexError
                self.matrix[key] = value.matrix[0]
            except IndexError:
                raise IndexSyntaxError
            except ValueError:
                raise MatrixValueError
        elif isinstance(key, tuple):
            if len(key) != 2:
                raise IndexSyntaxError

            row, col = key
            if isinstance(row, int) and isinstance(col, int):
                try:
                    if not isinstance(value, (int, float)):
                        raise ValueError
                    self.matrix[row][col] = value
                except IndexError:
                    raise IndexSyntaxError
                except ValueError:
                    raise MatrixValueError
            elif isinstance(row, slice) and isinstance(col, slice):
                try:
                    if self[row, col].rows != value.rows and self[row, col].cols != value.cols:
                        raise IndexError
                    rowindex = [i for i in range(self.rows)][row]
                    colindex = [i for i in range(self.cols)][col]

                    for i in range(len(rowindex)):
                        for j in range(len(colindex)):
                            self.matrix[rowindex[i]][colindex[j]] = value.matrix[i][j]
                except IndexError:
                    raise IndexSyntaxError
                except ValueError:
                    raise MatrixValueError
            else:
                raise MatrixValueError
        else:
            raise IndexSyntaxError

    # Self-defined methods
    # Feel free to define your own methods for class Matrix here

import time
x = [[i * 32 + j for j in range(32)] for i in range(32)]
a = Matrix(32, 32, x)
b = Matrix(32, 32, x)

start = time.process_time()
print((a * b)[0, 0])
print(time.process_time() - start)