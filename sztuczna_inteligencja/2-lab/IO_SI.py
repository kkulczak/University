import string
inFileStr = 'zad_input.txt'
outFileStr = 'zad_output.txt'


def getIndexs(board, charList):
    res = []
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] in charList:
                res.append((i, j))
    return list(res)


def readBoard():
    with open(inFileStr, 'r') as f:
        board = [
            [x for x in line if (x != '\n')]
            for line
            in f
        ]
        return board


def saveOtput(res):
    with open(outFileStr, 'w') as f:
        for x in res:
            f.write(x)
