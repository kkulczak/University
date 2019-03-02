import sys


outputStr = ""

def V(i,j):
    return 'V%d_%d' % (i,j)

def domains(Vs):
    return [ q + ' in 1..9' for q in Vs ]

def all_different(Qs):
    return 'all_distinct([' + ', '.join(Qs) + '])'

def get_column(j):
    return [V(i,j) for i in range(9)]

def get_raw(i):
    return [V(i,j) for j in range(9)]

def horizontal():
    return [ all_different(get_raw(i)) for i in range(9)]

def vertical():
    return [all_different(get_column(j)) for j in range(9)]

def get_block(a,b):
    res = []
    for i in range(a, a+3):
        for j in range(b, b+3):
            res.append(V(i,j))
    return res;

def squering():
    res = []
    for i in range(0, 9,3):
        for j in range(0, 9,3):
            res.append(all_different(get_block(i,j)))
    return res;

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
    variables = [ V(i,j) for i in range(9) for j in range(9)]

    outputStr += ':- use_module(library(clpfd)).\n'
    outputStr += 'solve([' + ', '.join(variables) + ']) :- '.format()


    cs = domains(variables) + vertical() + horizontal() + squering() #TODO: too weak contraints, add something!
    for i,j,val in assigments:
        cs.append( '%s #= %d' % (V(i,j), val) )

    print_constraints(cs, 4, 70),
    outputStr += '\n'
    outputStr += '    labeling([ff], [' +  ', '.join(variables) + ']).'
    outputStr += '\n'
    outputStr += ':- solve(X), open("prolog_result.txt", write, Stream),write(Stream, X),close(Stream), nl.\n'

if __name__ == "__main__":
    raw = 0
    triples = []

    with open("zad_input.txt", mode='r') as f:
        for x in f:
            x = x.strip()
            if len(x) == 9:
                for i in range(9):
                    if x[i] != '.':
                        triples.append( (raw,i,int(x[i])) )
                raw += 1
    sudoku(triples)
    f = open("zad_output.txt", mode='w')
    f.write(outputStr)

"""
89.356.1.
3...1.49.
....2985.
9.7.6432.
.........
.6389.1.4
.3298....
.78.4....
.5.637.48

53..7....
6..195...
.98....6.
8...6...3
4..8.3..1
7...2...6
.6....28.
...419..5
....8..79

3.......1
4..386...
.....1.4.
6.924..3.
..3......
......719
........6
2.7...3..
"""
