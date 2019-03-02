import random
from collections import namedtuple
import copy

BOK = 30
SX = -100
SY = 0
M = 8
White = 1
Black = -1


GameResult = namedtuple('GameResult', ['won', 'advantage'])


def initial_board():
    B = [[0] * M for i in range(M)]
    B[3][3] = White
    B[4][4] = White
    B[3][4] = Black
    B[4][3] = Black
    return B


class Board:
    dirs = [(0, 1), (1, 0), (-1, 0), (0, -1),
            (1, 1), (-1, -1), (1, -1), (-1, 1)]

    def __init__(self, weigthMatrix=None):
        self.player = White
        self.board = initial_board()
        self.fields = set()
        self.move_list = []
        self.history = []
        if weigthMatrix is not None:
            self.weigthMatrix = copy.deepcopy(weigthMatrix)
        for i in range(M):
            for j in range(M):
                if self.board[i][j] == 0:
                    self.fields.add((j, i))

    def getPlayer():
        return self.player

    def show(self):
        for i in range(M):
            res = []
            for j in range(M):
                b = self.board[i][j]
                if b == 0:
                    res.append('.')
                elif b == Black:
                    res.append('#')
                else:
                    res.append('o')
            print(''.join(res))
        print

    def draw(self):
        for i in range(M):
            for j in range(M):
                kwadrat(j, i, 'green')

        for i in range(M):
            for j in range(M):
                if self.board[i][j] == Black:
                    kolko(i, j, 'black')
                if self.board[i][j] == White:
                    kolko(i, j, 'white')

    def moves(self):
        res = []
        for (x, y) in self.fields:
            if any(self.can_beat(x, y, direction)
                   for direction in Board.dirs):
                res.append((x, y))
        if not res:
            return [None]
        return res

    def can_beat(self, x, y, d):
        dx, dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x, y) == -self.player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x, y) == self.player

    def get(self, x, y):
        if 0 <= x < M and 0 <= y < M:
            return self.board[y][x]
        return None

    def do_move(self, move):
        self.history.append(copy.deepcopy(self.board))
        self.move_list.append(move)
        if move is None:
            self.player = -self.player
            return
        x, y = move
        x0, y0 = move
        self.board[y][x] = self.player
        self.fields -= set([move])
        for dx, dy in self.dirs:
            x, y = x0, y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x, y) == -self.player:
                to_beat.append((x, y))
                x += dx
                y += dy
            if self.get(x, y) == self.player:
                for (nx, ny) in to_beat:
                    self.board[ny][nx] = self.player
        self.player = -self.player

    def result(self, gameEnded=False):
        res = 0
        if gameEnded:
            for y in range(M):
                for x in range(M):
                    res += self.board[y][x]
            return res * float('inf')
        for i, j in [(0, 0), (0, 7), (7, 0), (7, 7)]:
            if self.board[i][j] != 0:
                res += self.board[i][j] * 10
            else:
                for x in [self.get(i + x, j + y) for x, y in self.dirs]:
                    if x is not None:
                        res += x * -5
        if self.terminal():
            return res * float('inf')
        return res


    def revertMove(self):
        self.board = self.history.pop()
        self.player = -self.player
        madeMove = self.move_list.pop()
        if madeMove is not None:
            self.fields.add(madeMove)

    def terminal(self):
        if not self.fields:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] == self.move_list[-2] is None

    def random_move(self):
        ms = self.moves()
        if ms:
            return random.choice(ms)
        return [None]


if __name__ == '__main__':
    random.seed(10)
    for i in range(1000):
        B = Board()
        while True:
            # B.show()
            m = B.random_move()
            B.do_move(m)
            # input()
            if B.terminal():
                break

    # B.show()
    # print('Result', B.result())
    # print('Game over!')
    # input()
