import collections
import itertools
import operator
outputStr = ""

Point = collections.namedtuple('Point', ['row', 'col'])
Size = collections.namedtuple('Size', ['rows', 'cols'])
Data = collections.namedtuple('Data', ['rows', 'cols'])


data = tuple()
size = tuple()

tupForSquere = [(0, 0), (0, 1), (1, 0), (1, 1)]
tupForCol = [(0, 0), (0, 1), (0, 2)]
tupForRow = [(0, 0), (1, 0), (2, 0)]


def V(i, j):
    return 'V%d_%d' % (i, j)


def domains(Vs):
    return [q + ' in 0..1' for q in Vs]


def sumEqual(Qs, val):
    a = '{} #= {}'.format(' + '.join(Qs), val)
    # print(a)
    return a


def get_column(j):
    return [V(i, j) for i in range(size.rows)]


def get_raw(i):
    return [V(i, j) for j in range(size.cols)]


def horizontal():
    return [sumEqual(get_raw(i), data.rows[i]) for i in range(size.rows)]


def vertical():
    return [sumEqual(get_column(j), data.cols[j]) for j in range(size.cols)]


def get_block(a, b):
    res = []
    for i in range(a, a + 3):
        for j in range(b, b + 3):
            res.append(V(i, j))
    return res


def square_condition(block):
    block = tuple([V(x[0], x[1]) for x in block])
    (a, b, c, d) = block
    return '{0} + {3} #= {1} + {2} #\\/ {0} + {1} + {2} + {3} #= 1'.format(a, b, c, d)


def genSquares(p):
    res = []
    for x in tupForSquere:
        x = tuple(map(operator.add, p, x))
        if x[0] >= size.rows or x[1] >= size.cols:
            return None
        res.append(x)
    return res


def squering():
    allPoints = [Point(i, j) for j in range(size.cols)
                 for i in range(size.rows)]
    squares = [genSquares(x) for x in allPoints if genSquares(x) is not None]
    return [square_condition(x) for x in squares]


def genRow(p):
    res = []
    for x in tupForRow:
        x = tuple(map(operator.add, p, x))
        if x[0] >= size.rows or x[1] >= size.cols:
            return None
        res.append(x)
    return res


def genCol(p):
    res = []
    for x in tupForCol:
        x = tuple(map(operator.add, p, x))
        if x[0] >= size.rows or x[1] >= size.cols:
            return None
        res.append(x)
    return res


def lineCondition(block):
    block = tuple([V(x[0], x[1]) for x in block])
    (a, b, c) = block
    return '#\\ {1} #\\/ {0} #\\/ {2}'.format(a, b, c)

def lines():
    allPoints = [Point(i, j) for j in range(size.cols)
                 for i in range(size.rows)]
    squares = ([genRow(x) for x in allPoints if genRow(x) is not None] +
        [genCol(x) for x in allPoints if genCol(x) is not None])
    return [lineCondition(x) for x in squares]


def print_constraints(Cs, indent, d):
    global outputStr
    position = indent
    outputStr += (indent - 1) * ' '
    for c in Cs:
        outputStr += c + ','
        position += len(c)
        if position > d:
            position = indent
            outputStr += '\n'
            outputStr += (indent - 1) * ' '


def sudoku(assigments):
    global outputStr
    variables = [V(i, j) for i in range(size.rows) for j in range(size.cols)]

    outputStr += ':- use_module(library(clpfd)).\n'
    outputStr += 'solve([' + ', '.join(variables) + ']) :- '.format()

    cs = (domains(variables)
          + vertical()
          + horizontal()
          + squering()
          + lines()
          )
    # TODO: too weak contraints, add something!
    for i, j, val in assigments:
        cs.append('%s #= %d' % (V(i, j), val))

    print_constraints(cs, 4, 70),
    outputStr += '\n'
    outputStr += '    labeling([ff], [' + ', '.join(variables) + ']).'
    outputStr += '\n'
    outputStr += ':- solve(X), open("prolog_result.txt", write, Stream),\
                    write(Stream, X),close(Stream), nl.\n'


if __name__ == "__main__":
    raw = 0
    triples = []

    with open("zad_input.txt", mode='r') as f:
        rows = [int(x) for x in f.readline().split()]
        cols = [int(x) for x in f.readline().split()]
        for lineOfTriple in f:
            triples.append(tuple([int(x) for x in lineOfTriple.split()]))
    data = Data(rows, cols)
    size = Size(len(rows), len(cols))
    # print(allPoints)
    # itertools.
    # print(genSquares(allPoints))
    sudoku(triples)
    f = open("zad_output.txt", mode='w')
    f.write(outputStr)
