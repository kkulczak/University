import sys
import random
import collections

LOOP_MAX = 300

MetaReward = 100.
FileName = ""
Board = []

Actions = [(0, 0), (1, 0), (-1, 0), (0, 1), (0, -1),
           (1, 1), (1, -1), (1, 1), (-1, 1)]


PolicyBook = {}
# TempPolicyBook = {}


def Speeds():
    for vx in range(-3, 4):
        for vy in range(-3, 4):
            yield vx, vy


def readData():
    with open(FileName, 'r') as f:
        for x in f:
            Board.append([y for y in list(x) if y in [
                         'o', '#', '.', 'e', 's']])
    if Board[-1] == []:
        Board.pop()


def reward(state):
    x, y, _, _ = state
    if not (0 <= x < len(Board) and 0 <= y < len(Board[0])):
        return -100.
    if Board[x][y] == 'e':
        return MetaReward
    if Board[x][y] == '.':
        return -100.
    return -0.1


def readPolicyValue(state):
    x, y, _, _ = state
    if not (0 <= x < len(Board) and 0 <= y < len(Board[0])):
        return -100.
    if Board[x][y] == '.':
        return -100.
    if Board[x][y] == 'e':
        return MetaReward
    return PolicyBook[state][0]


def nextStates(state, action):
    x, y, vx, vy = state
    res = set()
    for oilAction in [(0, 0)] if Board[x][y] != 'o' else Actions:
        dvx, dvy = action  # (*)
        rx, ry = oilAction
        dvx += rx
        dvy += ry
        vx += dvx
        vy += dvy

        if vx > 3:
            vx = 3
        if vy > 3:
            vy = 3
        if vx < -3:
            vx = -3
        if vy < -3:
            vy = -3
        x += vx
        y += vy
        res.add((x, y, vx, vy))
    return res


def optPolicy(state, gamma):
    res = []
    for action in Actions:
        nss = nextStates(state, action)
        value = sum([
            ((1 / len(nss)) * (
                reward(ns) + gamma * readPolicyValue(ns)
            )) for ns in nss])
        res.append((value, action))
    return max(res)


def saveOtput():
    outFileName = FileName.split('/')[-1]
    with open("chars_test1/policy_for_{}".format(outFileName), 'w') as f:
        for k, v in PolicyBook.items():
            # print(k, v)
            string = "{} {} {} {} {} {}\n".format(
                k[1], k[0], k[3], k[2], v[1][1], v[1][0])
            f.write(string)


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("No path to map given!")
        exit()
    FileName = sys.argv[1]
    readData()
    for x in range(len(Board)):
        for y in range(len(Board[x])):
            if Board[x][y] == '.':
                continue
            for s in Speeds():
                PolicyBook[(x, y) + s] = (0., (0, 0)
                                          ) if Board[x][y] != 'e' else (MetaReward, (0, 0))
    # for k,v in PolicyBook.items():
    #     if k[0] == 0 and k[1] == 3:
    #         print(k, v)
    gamma = 0.99
    tempPolicy = {}
    for i in range(LOOP_MAX):
        epsilon = 0
        # print('.', end="")
        # if (i + 1) % 20 == 0:
        #     print('')
        for x in range(len(Board)):
            for y in range(len(Board[x])):
                if Board[x][y] == '.':
                    continue
                for s in Speeds():
                    state = (x, y) + s
                    value = optPolicy(state, gamma)
                    # if epsilon < abs(value[0] - readPolicyValue(state)):
                    #     print(state)
                    epsilon = max(epsilon, (value[0] - readPolicyValue(state)))
                    tempPolicy[state] = value
        temp = PolicyBook
        PolicyBook = tempPolicy
        tempPolicy = temp
        print(epsilon)
    print("Loop max: ", LOOP_MAX)
    saveOtput()
