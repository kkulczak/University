import multiprocessing as mp
from playing import *
from reversi_engine import *
import random
# import cProfile
# import pstats
# import io


def ReversiWorker(_):
    points = play(BasicPlayer)
    # if points < 0:
    # for i in random(8):
    #     for j in range(8):
    #         board[i][j] = -board[i][j]
    return (
        1 if points >= 0 else 0
        # ,
        # board
    )


if __name__ == '__main__':
    games = 100
    workers = mp.cpu_count()
    # pr = cProfile.Profile()
    # pr.enable()
    random.seed(1765)

    with mp.Pool(workers) as p:
        results = p.map(ReversiWorker, range(games))

    # resMatrix = [[0] * M for i in range(M)]
    # for x in results:
    #     for i in range(M):
    #         for j in range(M):
    #             resMatrix[i][j] += x[1][i][j]
    # print(resMatrix)

    # for b in resMatrix:
    #     print(b)
    wins = sum(results)
    # print(results)
    print('Won {} on {} games.   Percentage: {}%'.format(
        wins, games, wins / games * 100))
    # print('Mem used: {}, Slicec Counter {}'.format(memUsed, SliceCounter))
