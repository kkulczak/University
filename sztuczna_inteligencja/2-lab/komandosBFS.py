from komandos import *
import random
from komandosASTAR import aStar
import sys


def bfs(mem, initalState):
    nodes = 0
    mem.clear()
    mem.add(initalState)
    queue = deque()
    queue.append((initalState, []))
    while queue:
        nodes += 1
        (state, path) = queue.popleft()
        # showBoard(state)
        for (nextState, move) in genNewStates(state):
            if nextState in mem:
                continue
            mem.add(nextState)
            if isWin(nextState):
                print(format('Nodes: {}_'.format(nodes)), end='')
                return path + [move]
            queue.append((nextState, path + [move]))
    raise Exception('No solution for game')


def stateWithSmallerStateOrRand(state):
    stateSize = len(state)
    ans = random.choice(getMoves())
    for move in getMoves():
        newStateSize = len(apllyMove(state, move))
        if (stateSize > newStateSize):
            stateSize = newStateSize
            ans = move
    return (apllyMove(state, ans), ans)


if __name__ == '__main__':
    mem = set()
    initState = getInitialState(countPaths=False)
    counter = 0
    random.seed(0)
    while counter < 350:
        counter += 1
        ranState = initState
        randPath = []
        for i in range(100):
            (ranState, move) = stateWithSmallerStateOrRand(ranState)
            randPath.append(move)
        if len(ranState) <= 2:
            break
    print('Tries of random walk: {}'.format(counter))
    # showBoard(ranState)
    path = []
    if not isWin(ranState):
        path = bfs(mem, ranState)
    saveOtput(randPath + path)
