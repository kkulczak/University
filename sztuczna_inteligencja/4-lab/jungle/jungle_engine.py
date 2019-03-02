import numpy as np
import random
import copy

Animals = {
    'R': 1,
    'C': 2,
    'D': 3,
    'W': 4,
    'J': 5,
    'T': 6,
    'L': 7,
    'E': 8,
    'r': -1,
    'c': -2,
    'd': -3,
    'w': -4,
    'j': -5,
    't': -6,
    'l': -7,
    'e': -8,
    '.': 0
}

StartupSetup = '''L.....T.D...C.R.J.W.E.....................e.w.j.r.d...c.t.....l'''
TIME_NO_ATTACKS = 50


class Board:
    size = (9, 7)
    board = np.zeros(size)
    swamps = {(3, 1), (3, 2), (3, 4), (3, 5), (4, 1), (4, 2),
              (4, 4), (4, 5), (5, 1), (5, 2), (5, 4), (5, 5)}
    traps = {(0, 2), (0, 4), (1, 3), (8, 2), (8, 4), (7, 3)}
    caves = {1: (0, 3),
             (-1): (8, 3)}
    player = 1
    dirs = {(0, 1), (1, 0), (-1, 0), (0, -1)}
    figures = {}
    gameCounter = 0
    steps = 0

    def __init__(self, fromBoard=None, empty=False):
        if empty:
            return
        if fromBoard:
            self.figures = copy.deepcopy(fromBoard.figures)
            self.board = np.array(fromBoard.board, copy=True)
            self.player = fromBoard.player
            self.gameCounter = fromBoard.gameCounter
        for i in range(self.size[0]):
            for j in range(self.size[1]):
                num = Animals.get(StartupSetup[self.size[1] * i + j])
                self.board[i][j] = num
                if num:
                    self.figures[num] = (i, j)

    def swapPlayer(self):
        self.player *= -1

    def myFigures(self):
        for k, v in self.figures.items():
            if k * self.player >= 0:
                yield k, v

    def show(self):
        inv_map = {v: k for k, v in Animals.items()}
        for index, x in np.ndenumerate(self.board):
            if x != 0:
                sign = inv_map[x]
            elif index in self.traps:
                sign = '#'
            elif index in self.swamps:
                sign = '~'
            elif index == self.caves[1] or index == self.caves[-1]:
                sign = '*'
            else:
                sign = '.'
            print(sign, end=('' if index[1] != 6 else '\n'))
        print()

    def aviableMoves(self):
        res = []
        for f, pos in self.myFigures():
            for d in self.dirs:
                newPos = self.canMove(f, pos, d)
                if newPos:
                    res.append((f, newPos))
        if res:
            return res
        return [None]

    def canBeat(self, figure, newPos):
        toBeat = self.board[newPos] if newPos not in self.traps else 0
        if figure * toBeat > 0:
            return False
        if abs(figure) >= abs(toBeat):
            return True
        if abs(figure) == 1 and abs(toBeat) == 8:
            return True
        return False

    def isOnBoard(self, tuple):
        i, j = tuple
        return (0 <= i < 9) and (0 <= j < 7)

    def canMove(self, figure, oldPos, dir):
        newPos = tuple(np.add(oldPos, dir))
        if not self.isOnBoard(newPos):
            return False
        # Lew, Tygrys skacza przez stawy
        # Szcur wchodzi do wody
        if newPos in self.swamps:
            if figure not in [1, 6, 7]:
                return False
            if figure in [6, 7]:
                while newPos in self.swamps:
                    if self.board[newPos] != 0:
                        return False
                    newPos = tuple(np.add(newPos, dir))

        # Gracz nie mo»e wchodzi¢ do wlasnej jamy.
        if newPos == self.caves[self.player]:
            return False
        # Bicie

        if self.board[newPos] != 0:
            if figure == 1 and oldPos in self.swamps and newPos not in self.swamps:
                return False
        if not self.canBeat(figure, newPos):
            return False
        return newPos

    def executeMove(self, move):
        self.swapPlayer()
        self.steps += 1
        if not move:
            return
        self.gameCounter += 1
        f, newPos = move
        pos = self.figures[f]
        enemy = self.board[newPos]
        if enemy:
            del self.figures[enemy]
            self.gameCounter = 0
        self.board[pos] = 0
        self.board[newPos] = f
        self.figures[f] = newPos

    def isEnd(self):
        if self.gameCounter >= TIME_NO_ATTACKS:
            return True
        if self.board[self.caves[1]] != 0 or self.board[self.caves[-1]] != 0:
            return True
        return False

    def getWinner(self, why=False):
        if self.board[self.caves[1]] < 0:
            if why:
                print('Animal in cave')
            return -1
        if self.board[self.caves[-1]] > 0:
            if why:
                print('Animal in cave')
            return 1
        whiteBest = max(self.figures.keys())
        blackBest = abs(min(self.figures.keys()))
        if whiteBest > blackBest:
            if why:
                print('Beter animal on board')
            return 1
        if blackBest > whiteBest:
            if why:
                print('Beter animal on board')
            return -1
        dists = [[], None, []]
        for k, v in self.figures.items():
            k = 1 if k > 0 else -1
            dists[int(k + 1)].append(
                np.sum(np.abs(np.subtract(self.caves[-k], v)))
            )
        for x in [0, 2]:
            dists[x].sort()
        for i in range(min(len(dists[0]), len(dists[2]))):
            if dists[0][i] < dists[2][i]:
                if why:
                    print('Taxi distance')
                return -1
            if dists[2][i] < dists[0][i]:
                if why:
                    print('Taxi distance')
                return 1
        if why:
            print('Last move')
        return -self.player

    def setFigure(self, f, pos):
        oldPos = self.figures.get(f)
        if oldPos:
            self.board[oldPos] = 0
        self.figures[f] = pos
        self.board[pos] = f


def playGame(player, oponent, verbose=False):
    output = []
    inv_map = {v: k for k, v in Animals.items()}
    a = Board()
    while not a.isEnd():
        if a.player == 1:
            m = player(a)
        elif a.player == -1:
            m = oponent(a)
        a.executeMove(m)
        if verbose:
            print(inv_map[m[0]], a.steps, a.gameCounter)
            a.show()
            input()
            a.show()
    winner = 1 if a.getWinner(why=False) == 1 else 0
    # if winner:
    #     print('Player won. Game took {} steps.'.format(a.steps))
    # else:
    #     print('Opponent won. Game took {} steps.'.format(a.steps))
    return winner


# if __name__ == '__main__':
#     # random.seed(56364)
#     a = Board(empty=True)
#     a.setFigure(8, (8, 5))
#     a.setFigure(-2, (8, 4))
#     # a.setFigure(-1, (4,5))
#     a.show()
#     print(a.aviableMoves())
#     exit()
#     # print(a.aviableMoves())
#     # input()
#     while not a.isEnd():
#         moves = a.aviableMoves()
#         m = random.choice(moves)
#         # print(inv_map[m[0]], a.steps ,a.gameCounter)
#         a.executeMove(m)
#         # a.show()
#         # input()
#     print(a.gameCounter)
#     a.show()
#     print('Winner is: {} steps:{}'.format(a.getWinner(), a.steps))
