from sokobanASTAR import taxiDistance
from IO_SI import *
from sokoban import *

targets = set()
board = []
_dirs = {'U': (-1, 0), 'D': (1, 0), 'R': (0, 1), 'L': (0, -1)}
d = {}


def showBoard(state):
    for i in range(len(board)):
        for j in range(len(board[i])):
            tup = (i, j)
            if tup in state and tup in targets:
                print('B', end='')
            elif tup in state:
                print('S', end='')
            elif tup in targets:
                print('G', end='')
            elif board[i][j] != '#':
                print(' ', end='')
            else:
                print('#', end='')
        print()
    print()


def getMoves():
    return ['U', 'D', 'L', 'R']


def isWall(pos):
    (i, j) = pos
    return board[i][j] == '#'


def getInitialState(countPaths=True):
    # state => tuple(boxesTuple, keeperPos)
    global targets, board
    board = readBoard()
    targets = set(getIndexs(board, ['G', 'B']))
    state = set(getIndexs(board, ['B', 'S']))
    if countPaths:
        for t in targets:
            shortestPathToGoal(t)
    return tuple(sorted(state))


def isWin(state):
    for s in state:
        if s not in targets:
            return False
    return True


def apllyMove(state, move):
    newState = set()
    for x in state:
        pos = combineMove(x, _dirs[move])
        if isWall(pos):
            newState.add(x)
        else:
            newState.add(pos)
    return tuple(sorted(newState))


def genNewStates(state):
    states = []
    for move in getMoves():
        states.append((apllyMove(state, move), move))
    return states


targetsD = {}


def shortestPathToGoal(pos):
    targetsD[pos] = 0
    visited = set([pos])
    queue = deque([(pos, 0)])
    while queue:
        (state, steps) = queue.popleft()
        aviableSteps = [combineMove(state, _dirs[move]) for move in getMoves()
                        if not isWall(combineMove(state, _dirs[move]))]
        for nextState in aviableSteps:
            if nextState in visited:
                continue
            visited.add(nextState)
            if nextState in targetsD:
                targetsD[nextState] = min(steps + 1, targetsD[nextState])
            else:
                targetsD[nextState] = steps + 1
            queue.append((nextState, steps + 1))
    return


# def countShortestPathToTarget(G):
#     for v in G:
#         res = []
#         for t in targets:
#             res.append(d[(v, t)])
#         targetsD[v] = min(res)


def h(state):
    minDists = []
    minDists = [targetsD[s] for s in state]
    return max(minDists) + (len(state) // 12)


def hUnOpt(state):
    minDists = [targetsD[s] for s in state]
    minDists = sorted(minDists)
    res = 0
    for i in range(len(minDists)):
        res += minDists[i] * ((i + 1) ) ** 2
    return res


# def takeV():
#     res = []
#     for i in range(len(board)):
#         for j in range(len(board[i])):
#             v = (i, j)
#             if not isWall(v):
#                 res.append(v)
#     return res


# def warshalFloyd(G):
#     for v1 in G:
#         for v2 in G:
#             d[(v1, v2)] = float('inf')
#     for v in G:
#         for move in [_dirs[move] for move in getMoves()]:
#             vN = tuple(map(sum, zip(v, move)))
#             if not isWall(vN):
#                 d[(v, vN)] = 1
#     for u in G:
#         for v1 in G:
#             for v2 in G:
#                 if d[(v1, v2)] > d[(v1, u)] + d[(u, v2)]:
#                     d[(v1, v2)] = d[(v1, u)] + d[(u, v2)]
