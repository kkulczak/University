from playing import *
from reversi_engine import *
import random
import cProfile
import pstats
import io


SliceCounter = 0





if __name__ == '__main__':
    # pr = cProfile.Profile()
    # pr.enable()
    random.seed(1765)
    games = 100
    wins = 0
    for res, B in (play(BasicPlayer) for i in range(games)):
        if res > 0:
            wins += 1
        # B.show()
    print('Won {} on {} games.   Percentage: {}%'.format(
        wins, games, wins / games * 100))
    # pr.disable()
    # s = io.StringIO()
    # sortby = 'cumulative'
    # ps = pstats.Stats(pr, stream=s).sort_stats(sortby)
    # ps.print_stats()
    # print(s.getvalue())
