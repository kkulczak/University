from sklearn.neural_network import MLPClassifier
import pickle
from engine_reversi import Reversi

PATH_TO_DATA = "reversi_learning_data/smaller.dat"


def i(i, j):
    return i * 8 + j


def extractBonusAtributes(vec):
    res = []
    res.append(sum(vec))
    # coreners
    res.append(sum([x for i, x in enumerate(vec) if i in
                    [
        0 * 8 + 0,
        7 * 8 + 0,
        7 * 8 + 7,
        0 * 8 + 7
    ]]))
    # neigbours
    res.append(sum([x for i, x in enumerate(vec) if i in
                    [
        0 * 8 + 1, 1 * 8 + 0, 1 * 8 + 1,
        6 * 8 + 0, 6 * 8 + 1, 7 * 8 + 1,
        0 * 8 + 6, 1 * 8 + 6, 1 * 8 + 7,
        6 * 8 + 7, 6 * 8 + 6, 7 * 8 + 6
    ]]))
    # walls
    res.append(sum([x for i, x in enumerate(vec) if
                    i % 8 in [0, 7] or i // 8 in [0, 7]]))
    # mobility
    game = Reversi(vec)
    res.append(len(game.moves(1)) - len(game.moves(0)))

    return vec + res


def parseData():
    res = []
    with open(PATH_TO_DATA) as f:
        for x in f:
            a = x.split()
            vec = []
            for c in a[1]:
                if c == '_':
                    vec.append(0)
                elif c == '0':
                    vec.append(-1)
                elif c == '1':
                    vec.append(1)
            vec = extractBonusAtributes(vec)
            res.append((vec, int(a[0])))
    return res


if __name__ == '__main__':
    data = parseData()
    N = len(data) // 6
    test_data = data[: N]
    dev_data = data[N:]
    X = [x for (x, y) in dev_data]
    y = [y for (x, y) in dev_data]
    X_test = [x for (x, y) in test_data]
    y_test = [y for (x, y) in test_data]


    # creating model
    nn = MLPClassifier(hidden_layer_sizes=(60, 60, 10))
    # training model
    nn.fit(X, y)
    print("Dev score", nn.score(X, y))
    print("Test score", nn.score(X_test, y_test))
    # writing model
    filename = 'nn_advanced_atributes'
    pickle.dump(nn, open(filename, 'wb'))
