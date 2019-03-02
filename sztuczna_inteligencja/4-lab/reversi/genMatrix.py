from playing import *
from reversi_engine import *
import random


mem = {}
memUsed = 0
SliceCounter = 0


def BasicPlayer(board):
    global memUsed
    movesWithValues = []
    # return random.choice(board.moves())
    for m in board.moves():
        board.do_move(m)
        key = hashFromBoard(board.board)
        if key in mem:
            value = mem[key]
            memUsed += 1
        else:
            value = min_value(board, float("-inf"), -float("-inf"), 2)
            mem[key] = value
        movesWithValues.append((
            value,
            m
        ))
        board.revertMove()
    return max(movesWithValues)[1]


weigthMatrix = np.array([[28.6, 16.2, 16.6, 18.2, 15.8, 13.8, 12.8, 16.8],
                         [24., 19.6, 14.8, 17., 16.8, 14.2, 12.2, 16.2],
                         [24.2, 15.2, 16.2, 10.2, 8.2, 8.6, 12., 17.6],
                         [24.2, 14.6, 13.4, 21.4, 3.8, 13.2, 17.2, 20.],
                         [25., 20.4, 15.6, 15.4, 17.8, 12.2, 14.2, 17.8],
                         [25.6, 21.4, 18.8, 17.4, 7.6, 21.4, 10.4, 17.6],
                         [22.6, 19.6, 22.8, 23.8, 21., 16.6, 20.2, 15.4],
                         [24.2, 22.4, 24.8, 29.6, 27.8, 24.6, 16.4, 28.4]])

if __name__ == '__main__':
    random.seed(1765)
    matrix = Board().weigthMatrix
    games = 200
    wins = 0
    for i in range(games):
        res, B = play(BasicPlayer, numOfRandomMoves=10)
        matrix += B.board * 0.2 * (1. if res >= 0 else -1.)

    # print('Won {} on {} games.   Percentage: {}%'.format(
        # wins, games, wins / games * 100))
    # print('Mem used: {}, Slicec Counter {}'.format(memUsed, SliceCounter))
    print(matrix)
    B.show()
