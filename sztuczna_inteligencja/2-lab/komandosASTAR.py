from komandos import *
import heapq as H


def aStar(mem, initalState, heuristic):
    nodes = 0
    mem.clear()
    mem.add(initalState)
    queue = []
    queue.append((0, 0, initalState, []))
    while queue:
        nodes += 1
        # if nodes % 100000 == 0:
        #     print('NODES_{}'.format(nodes), end='')
        (priority, costOfComming, state, path) = H.heappop(queue)
        # showBoard(state)
        for (nextState, move) in genNewStates(state):
            if nextState in mem:
                continue
            mem.add(nextState)
            if isWin(nextState):
                print(format('Nodes: {}_'.format(nodes)), end='')
                return path + [move]
            H.heappush(queue, (
                heuristic(nextState) + costOfComming + 1,
                costOfComming + 1,
                nextState,
                path + [move]
            ))
    raise Exception('No solution for game')


if __name__ == '__main__':
    mem = set()
    initState = getInitialState()
    randPath = []
    path = []
    # for i in range(140):
    #     move = random.choice(getMoves())
    #     initState = apllyMove(initState, move)
    #     randPath.append(move)
    path = aStar(mem, initState, h)
    saveOtput(randPath + path)
