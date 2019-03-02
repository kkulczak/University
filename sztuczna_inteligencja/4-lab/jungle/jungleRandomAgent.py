import copy
import random
import cProfile
import pstats
import io
from jungle_engine import Board, Animals, playGame

AviSteps = 2500


def runGame(board):
    steps = 0
    while not board.isEnd():
        moves = board.aviableMoves()
        m = random.choice(moves)
        board.executeMove(m)
        steps += 1
    return board.getWinner(), steps


def randomAgent(board):
    moves = board.aviableMoves()
    d = {i: 0 for i in range(len(moves))}
    steps, i = 0, 0
    while steps < AviSteps:
        newBoard = Board(fromBoard=board)
        newBoard.executeMove(moves[i])
        winner, gameTook = runGame(newBoard)
        d[i] += 1 if winner == board.player else -1
        i = (i + 1) % len(moves)
        steps += gameTook
        # board.show()
        # newBoard.show()
        # input()
    # print(d, steps)
    choosenIndex = max([(v, k) for k, v in d.items()])
    # print(choosenIndex)
    # print(moves)
    return moves[choosenIndex[1]]




def randomMoves(board):
    return random.choice(board.aviableMoves())


if __name__ == '__main__':
    # pr = cProfile.Profile()
    # pr.enable()
    for i in range(10000):
        playGame(randomMoves, randomMoves)
    # pr.disable()
    # s = io.StringIO()
    # sortby = 'cumulative'
    # ps = pstats.Stats(pr, stream=s).sort_stats(sortby)
    # ps.print_stats()
    # print(s.getvalue())
