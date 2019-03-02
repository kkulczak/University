from IO_SI import *
from collections import deque
from utils import *

targets = []
board = []


def showBoard(boxes, pos):
    for i in range(len(board)):
        for j in range(len(board[i])):
            if (i, j) in boxes:
                print('B', end='')
            elif (i, j) in pos:
                print('K', end='')
            elif board[i][j] in ['B', 'K']:
                print('.', end='')
            else:
                print(board[i][j], end='')
        print()


def getInitialState():
    # state => tuple(boxesTuple, keeperPos)
    global targets, board
    board = readBoard()
    keeper = (getIndexs(board, ['K', '+']))[0]
    targets = tuple(getIndexs(board, ['G', '*', '+']))
    boxes = tuple(getIndexs(board, ['B', '*']))
    return (boxes, keeper)


def getTargets():
    return targets


def recoverMove(prevPos, pos):
    return (pos[0] - prevPos[0], pos[1] - prevPos[1])


def translateMove(move):
    dict = {
        (0, 1): 'R',
        (0, -1): 'L',
        (1, 0): 'D',
        (-1, 0): 'U'
    }
    return dict.get(move)


def combineMove(pos, move):
    return tuple(map(sum, zip(pos, move)))


def reverseMove(move):
    return (move[0] * -1, move[1] * -1)


def getMoves():
    return zip([0, 0, 1, -1], [1, -1, 0, 0])


def isWall(pos):
    (i, j) = pos
    return board[i][j] == 'W'


def isWin(boxes):
    for box in boxes:
        if box not in targets:
            return False
    if (len(set(boxes)) != len(boxes)):
        raise Exception('One box on another!!!')
    return True


def keeperStep(state):
    (boxes, keeper) = state
    moves = getMoves()
    newStates = []
    for move in moves:
        newKeePos = combineMove(keeper, move)
        if isWall(newKeePos):
            continue
        if newKeePos not in boxes:
            newStates.append((boxes, newKeePos))
            continue
        newBoxPos = combineMove(newKeePos, move)
        if newBoxPos in boxes or isWall(newBoxPos):
            continue
        else:
            i = boxes.index(newKeePos)
            newStates.append((
                replaceTuple(boxes, newKeePos, newBoxPos),
                newKeePos
            ))
    return list(newStates)


def canKeeperMove(keeper, move):
    newPos = combineMove(keeper, move)
    if isWall(newPos):
        return False
    return True


def canMoveWithoutEffect(box, move, boxes):
    newPos = combineMove(box, move)
    if isWall(newPos) or newPos in boxes:
        return False
    return True


def pathFromTo(start, end, boxes):
    if isWall(start) or start in boxes:
        return None
    visited = set()
    visited.add(start)
    if start == end:
        return []
    q = deque()
    q.append((start, []))
    while q:
        (pos, path) = q.popleft()
        if pos == end:
            return path[::-1]
        for move in getMoves():
            newPos = combineMove(pos, move)
            if newPos in visited or isWall(newPos) or newPos in boxes:
                continue
            visited.add(newPos)
            newPath = list(path)
            newPath.append(translateMove(reverseMove(move)))
            q.append((newPos, newPath))
    return None


def genNewStates(state):
    (boxes, keeper) = state
    res = []
    for box in boxes:
        for move in getMoves():
            keeperPath = pathFromTo(combineMove(box, move), keeper, boxes)
            if keeperPath is None:
                continue
            boxAfterPush = combineMove(box, reverseMove(move))
            if isWall(boxAfterPush) or boxAfterPush in boxes:
                continue
            newBoxes = replaceTuple(boxes, box, boxAfterPush)
            newKeeper = box
            keeperPath.append(translateMove(reverseMove(move)))
            res.append(((newBoxes, newKeeper), keeperPath))
    return res
