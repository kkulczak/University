# import cProfile
# import pstats
# import io
from picture import *

# pr = cProfile.Profile()
# pr.enable()


def out(p):
    for i in range(2):
        print([len(x) for x in p.perms[i]])


if __name__ == '__main__':
    p = Picture()
    p.genPerms()
    p.detuctAll()
    p.backtrackLoop()
    p.saveOtput()
    # pr.disable()
    # s = io.StringIO()
    # sortby = 'cumulative'
    # ps = pstats.Stats(pr, stream=s).sort_stats(sortby)
    # ps.print_stats()
    # print(s.getvalue())
