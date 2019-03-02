def howManyHaveToFlip(list, windowSize):
    oneSymbol = 1
    leastFlips = len(list)
    OnesInList = 0
    for x in list:
        if x == oneSymbol:
            OnesInList += 1
    OnesInWindow = 0
    for i in range(windowSize):
        if list[i] == oneSymbol:
            OnesInWindow += 1

    for i in range(len(list) - windowSize - 1):
        leastFlips = min(
            (windowSize - OnesInWindow) + (OnesInList - OnesInWindow),
            leastFlips
        )
        if list[i] == oneSymbol:
            OnesInWindow -= 1
        if list[i + windowSize] == oneSymbol:
            OnesInWindow += 1
    return leastFlips

