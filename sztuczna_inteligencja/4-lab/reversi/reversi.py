import numpy as np
from constants import *
import itertools


class Player():
    def __init__(self, val):
        self.val = val

    def setNext(self):
        self.val = White if self.val == Black else Black
        return self.val

    def get(self):
        return self.val

    def rev(self):
        return White if self.val == Black else Black


class Reversi:

    def __init__(self):
        self.tab = np.zeros((8, 8), dtype=np.int)
        for (i, j) in [(3, 3), (4, 4)]:
            self.tab[i][j] = White
        for (i, j) in [(3, 4), (4, 3)]:
            self.tab[i][j] = Black
        self.turn = Player(White)

    def show(self):
        print()
        for row in self.tab:
            for y in row:
                print(reversiBoard[y], end='')
            print()
        print()

    def aviableMoves(self):
        moves = [x for x in itertools.product(
            range(8), range(8)) if self.tab[x] == Empty]
        return [x for x in moves
                if self.executeMove(x, checkOnly=True)]

    def allLines(self, pos):
        i, j = pos
        yield self.tab[i][j + 1:]
        yield self.tab[i][:j][::-1]
        yield self.tab[:, j][i + 1:]
        yield self.tab[:, j][:i][::-1]
        yield np.diag(self.tab, (j - i))[j + 1:]
        yield self.tab.diagonal(j - i)[:j][::-1]
        newJ = 7 - j
        yield np.fliplr(self.tab).diagonal(newJ - i)[newJ + 1:]
        yield np.fliplr(self.tab).diagonal(newJ - i)[:newJ][::-1]

    def executeMove(self, pos, checkOnly=False):
        self.tab = np.arange(64).reshape(8, 8)
        for c in self.allLines((4, 4)):
            c[0] = 100
            print(self.tab)
        for c in self.allLines(pos):
            revColorCounter = 0
            for x in c:
                if x == Empty:
                    revColorCounter = 0
                    break
                elif x == self.turn.get():
                    break
                revColorCounter += 1
            if 0 < revColorCounter < len(c):
                if checkOnly:
                    return True
                else:
                    for i in range(revColorCounter):
                        c[i] = self.turn.get()
        if not checkOnly:
            self.tab[pos] = self.turn.get()
            self.turn.setNext()
        return False
