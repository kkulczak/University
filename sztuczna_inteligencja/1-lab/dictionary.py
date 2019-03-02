import json
import io


dictionary = {}

mem = {}

def findOpt(i, dataStr):
    if mem.get(i) is not None:
        return

    actRes = 0
    bestPrev = -1

    for j in range(i + 1, len(dataStr) + 1, 1):
        tempStr = dataStr[i:j]
        # print(tempStr)

        if dictionary.get(tempStr) is not None:
            findOpt(j, dataStr)
            newVal = len(tempStr) ** 2 + mem[j][0]

            if newVal > actRes:
                actRes = newVal
                bestPrev = j

    mem[i] = (actRes, bestPrev)
    return


def getRes(i, dataStr):
    if i is None:
        return
    (a, b) = mem[i]
    if b < 0:
        b = None
    print(dataStr[i:b], end=' ')
    getRes(b, dataStr)
    return


# with io.open(pathDict,'r',encoding='utf8') as f:
#     text = f.read()
# # process Unicode text
# with io.open(filename,'w',encoding='utf8') as f:
#     f.write(text)


pathDict = '/home/kku/Dropbox/Data/words_for_ai1.txt'
pathTadeusz = '/home/kku/Dropbox/Data/pan_tadeusz.txt'


def main():
    dict_data = io.open(pathDict, 'r', encoding='utf8')
    for line in dict_data:
        if not line.isspace():
            dictionary[line[:-1]] = 1
    data = io.open(pathTadeusz, 'r', encoding='utf8')
    for line1 in data:
        dataStr = line1[:-1]
        mem.clear()
        findOpt(0, dataStr)
        getRes(0, dataStr)
        print()


main()
# print(json.dumps(mem))
# print(dictionary['pierwsza'])
