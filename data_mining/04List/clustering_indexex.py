import numpy as np


def distances(X, r):
    a = np.sum(X ** 2, axis=1)[np.newaxis, :]
    b = np.sum(r ** 2, axis=1)[:, np.newaxis]
    c = - 2 * (r @ X.T)
    dists = c + a + b
    return np.sqrt(dists)


def dunn_index(X, labels, C):
    k = np.unique(labels).size

    dissimilarity = min((
        np.min(
            distances(
                X[labels == i],
                X[labels == j]
            )
        )
        for i in range(k)
        for j in range(i + 1, k)
    ))

    diameter = max((
        np.max(
            distances(
                X[labels == i],
                X[labels == i])
        )
        for i in range(k)
    ))

    return dissimilarity / diameter


def davies_bouldin_index(X, labels, C):
    k = np.unique(labels).size

    diameters = [
        np.sqrt(
            np.sum(
                distances(X[labels == i], np.array([C[i]])) ** 2
            ) / np.sum(labels == i)
        )
        for i in range(k)
    ]

    cetners_distances = distances(C, C)

    return np.sum([
        max((
            (diameters[i] + diameters[j]) / cetners_distances[i][j]
            for j in range(k)
            if i != j
        ))
        for i in range(k)
    ]) / k
