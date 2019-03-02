from sokoban import *
from collections import deque
from IO_SI import saveOtput


def bfs(mem, initalState):
    mem.clear()
    mem[initalState] = None
    queue = deque([initalState])
    nodes = 0
    while queue:
        nodes += 1
        state = queue.popleft()
        aviableSteps = keeperStep(state)
        for nextState in aviableSteps:
            if nextState in mem:
                continue
            if isWin(nextState[0]):
                mem[nextState] = state
                print('Nodes released: {}'.format(nodes))
                return nextState
            queue.append(nextState)
            mem[nextState] = state
    raise Exception('No solution for game')


def recoverSolution(mem, lastState):
    res = []
    state = lastState
    while mem[state] is not None:
        res.append(translateMove(recoverMove(mem[state][1], state[1])))
        state = mem[state]
    return res[::-1]


if __name__ == '__main__':
    mem = {}
    initalState = getInitialState()
    winState = bfs(mem, initalState)
    resList = recoverSolution(mem, winState)
    saveOtput(resList)
