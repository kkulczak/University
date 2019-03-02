from collections import deque
MAX_BOARD = 8
WHITE = 0
BLACK = 2
figures = ('♔', '♖', '♚')


def nextColor(col):
    if col == WHITE:
        return BLACK
    return WHITE


def isOnBoard(pos):
    return pos[0] in range(MAX_BOARD) and pos[1] in range(MAX_BOARD)


def pos2d(s):
    """
        s - position on the board, for example 'a3' or 'hMAX_BOARD'
    """
    column = ord(s[0]) - ord('a')
    row = ord(s[1]) - ord('1')
    return column, row


def posToChar(pos):
    column, row = pos
    return (str(chr(column + ord('a'))) + str(row + 1))


def stateToCharState(state):
    if state is None:
        return('', '', '')
    return tuple([posToChar(x) for x in state])


def combinePos(pos, pos1):
    return (pos[0] + pos1[0], pos[1] + pos1[1])


def around(pos):
    i = [1, 1, 1, 0, 0, -1, -1, -1]
    j = [-1, 0, 1, -1, 1, -1, 0, 1]
    # print(state[color])
    moves = [combinePos(pos, (i[k], j[k])) for k in range(len(i))]
    return moves


def kingMoves(state, color):
    moves = around(state[color])
    return [k for k in moves if isOnBoard(k) and k not in state]


def KingMovesWithCheck(state, color):
    a = kingMoves(state, color)
    b = kingMoves(state, nextColor(color))
    # print(a)
    # print(b)
    return [x for x in a
            if x not in b]


def towerMoves(state):
    pos = state[1]
    j = pos[0]
    a = [(i, pos[1]) for i in range(j - 1, -1, -1) if isOnBoard((i, pos[1]))]
    b = [(i, pos[1]) for i in range(j + 1, MAX_BOARD) if isOnBoard((i, pos[1]))]
    j = pos[1]
    c = [(pos[0], i) for i in range(j - 1, -1, -1) if isOnBoard((pos[0], i))]
    d = [(pos[0], i) for i in range(j + 1, MAX_BOARD) if isOnBoard((pos[0], i))]
    aviableMoves = []
    for x in [a, b, c, d]:
        for y in x:
            if y in state:
                break
            aviableMoves.append(y)
    return aviableMoves


def towerAttacks(state):
    wk, wt, bk = state
    (i, j) = wt
    return [item for sublist in (([(i, x), (x, j)] for x in range(0, MAX_BOARD))) for item in sublist]


def genAllStates(state, color):
    wk, wt, bk = state
    kMoves = KingMovesWithCheck(state, color)
    tMoves = towerMoves(state)
    if color == BLACK:
        kMoves = [x for x in kMoves if
                  (x not in towerAttacks(state))]
        return [(wk, wt, x) for x in kMoves]
    else:
        res = ([(x, wt, bk) for x in kMoves] +
               [(wk, x, bk) for x in tMoves])
        return res


def attackedByWhite(state):
    return towerAttacks(state) + kingMoves(state, WHITE)


mem = {}
log = []


def bfs(StartState, StartColor):
    queue = deque([(StartState, StartColor, 0)])
    mem[StartState] = (0, StartColor, None)
    while queue:
        state, color, steps = queue.popleft()
        log.append((stateToCharState(state), steps, mem.get(state)))
        nextStates = genAllStates(state, color)
        if len(nextStates) == 0:
            if color == WHITE:
                raise Exception('IMPOSIBLE')
            if state[BLACK] in attackedByWhite(state):
                if state[1] in around(state[BLACK]):
                    # wieza w poblizu czarnego krola
                    if state[1] in around(state[WHITE]):
                        # Jezeli zbicie wiezy bedzie podlozeniem po dkrola
                        return (steps, state)
                    else:
                        continue
                return (steps, state)
        for x in nextStates:
            if x not in mem and x != state:
                mem[x] = (steps + 1, color, state)
                queue.append((x, nextColor(color), steps + 1))
    raise Exception("Empty")


StartingColor = WHITE


def startTuple():
    str = 'black a2 e4 a4'
    [x, a, b, c] = str.split()
    StartingColor = x
    return ((a, b, c), color)


def parseLine(str):
    [color, a, b, c] = str.split()
    state = (tuple([pos2d(i) for i in [a, b, c]]))
    return (WHITE if color == 'white' else BLACK, state)


def show_path(resState):
    res = [resState]
    it = resState
    while it is not None:
        a, b, prevState = mem[it]
        if prevState is None:
            return res[::-1]
        res.append(prevState)
        it = prevState
    return res


if __name__ == '__main__':
    # state = ((1, 0), (0, 0), (1, 2))
    # a = KingMovesWithCheck(state, WHITE)
    # print(a)
    file = open('zad1_input.txt', 'r')
    lines = file.readlines()
    resFile = open('zad1_output.txt', 'w')
    for x in lines:
        mem.clear()
        log.clear()
        (color, state) = parseLine(x)
        (res, lastState) = bfs(state, color)
        resFile.write('{}\n'.format(res))

# print(res)
# for x in mem:
#     print(x, end='\t')
#     print(mem[x])
