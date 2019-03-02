from komandos import *
import heapq as H
from komandosBFS import stateWithSmallerStateOrRand, bfs
from komandosASTAR import aStar





MAX_STATE = 5
MAX_COUNTER = 50

if __name__ == '__main__':
    mem = set()
    initState = getInitialState()
    ranState = initState
    randPath = []
    counter = 0
    path = []
    if not isWin(ranState):
        path = aStar(mem, ranState, hUnOpt)
    saveOtput(randPath + path)
