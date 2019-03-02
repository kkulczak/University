import numpy as np
from copy import deepcopy


inFileStr = 'zad_input.txt'
outFileStr = 'zad_output.txt'
Row = 0
Col = 1
Black = 1
White = -1
Grey = 0


class checkType:
    def __init__(self, t):
        self.t = t

    def rev(self):
        return checkType(0 if self.t else 1)

    def val(self):
        return self.t

    def __gt__(self, newT):
        return self.val() > newT.val()


class ImpossibleConstraints(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


class Picture:
    def __init__(self):
        self.toDeduct = set()
        self.stack = []
        with open(inFileStr, 'r') as f:
            rows = []
            columns = []
            line = f.readline().split(" ")
            self.size = tuple([int(x) for x in line[:2]])
            self.tab = np.full(self.size, Grey, dtype=int)
            for i in range(self.size[Row]):
                rows.append([int(x) for x in f.readline().split(" ")])
            for i in range(self.size[Col]):
                columns.append([int(x) for x in f.readline().split(" ")])
            self.data = (rows, columns)

    def saveOtput(self):
        with open(outFileStr, 'w') as f:
            for x in self.tab:
                for y in x:
                    if y == White:
                        f.write('.')
                    elif y == Black:
                        f.write('#')
                    else:
                        raise Exception('Wrong bit on tab')
                f.write('\n')

    def show(self):
        print(self.size)
        print(self.tab, end='\n\n')
        print(self.data[Row], self.data[Col])

    def showTab(self):
        print(self.tab)

    def genPerms(self):
        pemrsRows = []
        for x, y in zip(self.tab, self.data[Row]):
            pemrsRows.append(genPermForRow(len(x), y))
        permsCols = []
        for x, y in zip(self.tab.T, self.data[Col]):
            permsCols.append(genPermForRow(len(x), y))
        self.perms = (pemrsRows, permsCols)

    def deductPerms(self):
        for i in [Row, Col]:
            for j in range(self.size[i]):
                self.deductDomain(checkType(i), j)

    def deductDomain(self, t, index):
        wholeDomain = self.allPerms[t.val()][index]
        row = self.tab[index] if t.val() == Row else self.tab[:, index]
        for d in wholeDomain:
            if d in self.perms[t.val()][index]:
                break
            addToPerms = True
            # print(self.tab[t.val()])
            # print(row)
            for i in range(len(row)):
                if row[i] != Grey and row[i] != d[i]:
                    addToPerms = False
                    break
            if addToPerms:
                self.perms[t.val()][index].add(d)

    def reducePermSet(self,
                      t,
                      rowIndex,
                      bitIndex
                      ):
        row = self.tab[rowIndex] if t.val() == Row else self.tab[:, rowIndex]
        perms = self.perms[t.val()][rowIndex]
        # print(len(perms), end='\t')
        toRemove = []
        if row[bitIndex] == 0:
            raise Exception('DUPA')
        for p in perms:
            if p[bitIndex] != row[bitIndex]:
                toRemove.append(p)
        for r in toRemove:
            perms.remove(r)
        if len(perms) == 0:
            raise ImpossibleConstraints('')
        # print(len(perms), end='\n\n')

    def deductRow(self, t, index):
        row = self.tab[index] if t.val() == Row else self.tab[:, index]
        perms = self.perms[t.val()][index]
        # print(perms, t.val(), index, self.data[t.val()][index])
        acc = (0,) * self.size[t.rev().val()]
        for p in perms:
            acc = tuple(map(sum, zip(acc, p)))
        for i in range(len(acc)):
            if abs(acc[i]) // len(perms) == 1:
                color = White if acc[i] < 0 else Black
                if color != row[i]:
                    row[i] = color
                    self.reducePermSet(t.rev(), i, index)
                    self.toDeduct.add((t.rev(), i))
        # self.showTab()
        # input()

# <<<<<<< Updated upstream
    # def detuctAll(self):
    #     t = checkType(Row)
    #     for j in range(2):
    #         t = t.rev()
    #         for i in range(self.size[t.val()]):
    #             self.deductRow(t, i)
# # =======
    def detuctAll(self):
        for i in [Row, Col]:
            for j in range(self.size[i]):
                self.toDeduct.add((checkType(i), j))
                # self.toDeduct.add((checkType(i), j))
        while self.toDeduct:
            (t, i) = self.toDeduct.pop()
            self.deductRow(t, i)

    def permsSizes(self):
        return [len(x) for x in self.perms[Row] + self.perms[Col]]

    def domainsSizes(self):
        lens = []
        for j in [Row, Col]:
            lens += [
                (len(x), checkType(j), i)
                for (i, x)
                in enumerate(self.perms[j]) if len(x) > 1]
        return lens

    def isSolved(self):
        for x in self.permsSizes():
            if x != 1:
                return False
        return True

    def stackPush(self):
        (value, t, index) = min(self.domainsSizes())
        self.stack.append((
            deepcopy(self.perms),
            deepcopy(self.tab),
            list(self.perms[t.val()][index]),
            (t, index)
        ))

    def stackPop(self):
        if len(self.stack) == 0:
            raise Exception('Out Of Domains')
        (perms, tab, domain, id) = self.stack[-1]
        # if len(self.stack) == 1:
        #     print('dlugosc pierwszej dziedziny', len(domain))
        # if len(self.stack) == 2:
        #     print('dlugosc drugiej dziedziny', len(domain))
        (t, index) = id
        if len(domain) == 0:
            self.stack.pop()
            return self.stackPop()
        # self.perms = deepcopy(perms)
        for i in [Row, Col]:
            for j in range(self.size[i]):
                if len(self.perms[i][j]) != len(perms[i][j]):
                    for x in perms[i][j]:
                        self.perms[i][j].add(x)
        self.tab = deepcopy(tab)
        varValue = domain.pop()
        self.perms[t.val()][index].clear()
        self.perms[t.val()][index].add(varValue)
        return id

    def backtrackLoop(self):
        counter = 0
        self.stackPush()
        t, index = self.stackPop()
        while True:
            counter += 1
            if counter % 100 == 0:
                print(counter)
            try:
                self.deductRow(t, index)
                while self.toDeduct:
                    (t, i) = self.toDeduct.pop()
                    self.deductRow(t, i)
                if self.isSolved():
                    print(counter)
                    return
                self.stackPush()
                t, index = self.stackPop()
            except ImpossibleConstraints as e:
                t, index = self.stackPop()


def genPermForRow(rowLen, data):
    perms = set()
    genPermForInterval([], data, 0, rowLen, perms)
    return perms


def genPermForInterval(
        row,
        data,
        startIndex,
        rowLen,
        perms):
    if not data:
        perms.add(tuple(row + [White] * (rowLen - startIndex)))
        return None
    if sum(data) + len(data) - 1 + startIndex > rowLen:
        return 'TO_LONG'
    for i in range(startIndex, rowLen - data[0] + 1):
        thisBlock = [White] * (i - startIndex) + [Black] * \
            data[0] + ([] if len(data) == 1 else [White])
        temp = genPermForInterval(row + thisBlock, data[1:],
                                  startIndex + len(thisBlock), rowLen, perms)
        if temp == 'TO_LONG':
            return None
    return None
