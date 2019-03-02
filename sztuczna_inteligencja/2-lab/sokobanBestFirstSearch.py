from sokoban import *
import heapq as H
from IO_SI import saveOtput
from sokobanASTAR import h
import itertools


def recoverSolution(mem, lastState):
    state = lastState
    solution = []
    while mem.get(state) is not None:
        (state, path) = mem.get(state)
        solution.append(path)
    return list(itertools.chain.from_iterable(solution[::-1]))


def bestFirstSearch(mem, initState):
    mem.clear()
    mem[initState] = None
    queue = [(0, initState)]
    nodes = 0
    while queue:
        nodes += 1
        (_, state) = H.heappop(queue)
        for (nextState, path) in genNewStates(state):
            if nextState in mem:
                continue
            hValue = h(nextState)
            mem[nextState] = (state, path)
            if hValue == 0:
                print('Nodes resolved: {}'.format(nodes))
                return nextState
            if hValue < float('inf'):
                H.heappush(queue, (
                    hValue,
                    nextState,
                ))
    raise Exception('No solution for game')


if __name__ == '__main__':
    mem = {}
    initalState = getInitialState()
    lastState = bestFirstSearch(mem, initalState)
    resList = recoverSolution(mem, lastState)
    saveOtput(resList)
