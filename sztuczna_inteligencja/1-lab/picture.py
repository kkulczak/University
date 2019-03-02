# from picture_row import howManyHaveToFlip
import random


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
    # print(list, windowSize)
    for i in range(len(list) - windowSize):
        leastFlips = min(
            (windowSize - OnesInWindow) + (OnesInList - OnesInWindow),
            leastFlips
        )
        if list[i] == oneSymbol:
            OnesInWindow -= 1
        if list[i + windowSize] == oneSymbol:
            OnesInWindow += 1
    leastFlips = min(
        (windowSize - OnesInWindow) + (OnesInList - OnesInWindow),
        leastFlips
    )
    return leastFlips


rowList = None
colList = None
rowNums = None
colNums = None


def secondObject(object):
    global rowList
    global colList
    if object is colList:
        return rowList
    elif object is rowList:
        return colList
    else:
        raise Exception('Wrong fromObject')


def getNums(object):
    global rowList
    global colList
    global rowNums
    global colNums
    if object is colList:
        return colNums
    elif object is rowList:
        return rowNums
    else:
        raise Exception('Wrong object')


def updateObject(fromObject, i=None, j=None):
    intoObject = secondObject(fromObject)

    if j is not None:
        intoObject[j][i] = fromObject[i][j]
        return

    for j in range(len(fromObject[i])):
        intoObject[j][i] = fromObject[i][j]


def flipBit(obj, i, j):
    obj[i][j] ^= 1
    updateObject(obj, i, j)


def changeSublist(picture, index):

    bestBitPlace = (2 * len(picture) + 1, None)
    for i in range(len(picture[index])):
        flipBit(picture, index, i)

        a = howManyHaveToFlip(picture[index], getNums(picture)[index])
        b = howManyHaveToFlip(secondObject(picture)[i], getNums(secondObject(picture))[i])
        flipsSum = a + b
        # print(i, a, b)

        if bestBitPlace[0] > flipsSum:
            bestBitPlace = (flipsSum, i)

        flipBit(picture, index, i)

    flipBit(picture, index, bestBitPlace[1])


def printImage(ourFile):
    for i in range(len(rowList)):
        for j in range(len(rowList[i])):
            if rowList[i][j] != colList[j][i]:
                raise Exception('Naruszenie spojnosci danych')
            c = '#' if rowList[i][j] == 1 else '.'
            ourFile.write(c)

        ourFile.write('\n')
    ourFile.write('\n')


def isOk():
    for i in range(len(rowList)):
        if howManyHaveToFlip(rowList[i], rowNums[i]) != 0:
            return False
    for i in range(len(colList)):
        if howManyHaveToFlip(colList[i], colNums[i]) != 0:
            return False
    return True


if __name__ == '__main__':
    # input_file: zad5_input.txt
    # output_file: zad5_output.txt
    rowList = []
    colList = []
    colNums = []
    rowNums = []
    inFile = open('zad5_input.txt', 'r')
    outFile = open('zad5_output.txt', 'w')
    (size, size1) = [int(x) for x in inFile.readline().split()]
    for i in range(size):
        rowNums.append(int(inFile.readline()))
    for i in range(size):
        colNums.append(int(inFile.readline()))

    colList = [[0 for x in range(size1)] for i in range(size)]
    rowList = [[0 for x in range(size)] for i in range(size1)]

    while True:
        for i in range(size):
            for j in range(size):
                rowList[i][j] = random.randint(0, 1)

        for i in range(len(rowList)):
            updateObject(rowList, i)

        for i in range(4000):
            data = [rowList, colList]

            changeSublist(data[random.randint(0, 1)], random.randint(0, size - 1))
            if isOk():
                printImage(outFile)
                break
        if isOk():
            break
