from sokoban import *
import heapq as H
from IO_SI import saveOtput
from sokobanBFS import recoverSolution


def taxiDistance(pos1, pos2):
    res = 0
    for i in range(2):
        res += abs(pos1[i] - pos2[i])
    return res


def h(state):
    targets = getTargets()
    boxes = list(state[0])
    res = 0
    for (i, j) in boxes:
        if ((isWall((i + 1, j)) or isWall((i - 1, j))) and
                (isWall((i, j + 1)) or isWall((i, j - 1)))) and \
                (i, j) not in targets:
            return float('inf')
    for t in targets:
        if not boxes:
            break
        distances = [(taxiDistance(t, b), b) for b in boxes]
        dist = min(distances)
        res += dist[0]
        boxes.remove(dist[1])
    return res


def aStar(mem, initalState):
    mem.clear()
    mem[initalState] = None
    queue = [(0, 0, initalState)]
    while queue:
        (priority, costOfComming, state) = H.heappop(queue)
        aviableSteps = keeperStep(state)
        for nextState in aviableSteps:
            if nextState in mem:
                continue
            if isWin(nextState[0]):
                mem[nextState] = state
                return nextState

            H.heappush(queue, (
                h(nextState) + costOfComming + 1,
                costOfComming + 1,
                nextState
            ))
            mem[nextState] = state
    raise Exception('No solution for game')


if __name__ == '__main__':
    mem = {}
    initalState = getInitialState()
    winState = aStar(mem, initalState)
    resList = recoverSolution(mem, winState)
    saveOtput(resList)
