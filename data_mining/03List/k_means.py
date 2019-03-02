import numpy as np
import itertools


def distances(X, r):
#     a = np.sum(X ** 2, axis=1)[np.newaxis, :]
    b = np.sum(r ** 2, axis=1)[:, np.newaxis]
    c = - 2 * (r @ X.T)
    dists = c + a + b
    return dists


def K_MEANS(X, k):
    r_ids = np.random.choice(X.shape[0], replace=False, size=k)
    r = X[r_ids]
    prev_grouping = None
    grouping = None
    while prev_grouping is None or not np.all(grouping == prev_grouping):
        dists = distances(X, r)
        prev_grouping = grouping
        grouping = dists.argmin(axis=0)
        for i in range(k):
            if np.any(grouping == i):
                new_middle = X[grouping == i].mean(axis=0)
                r[i] = new_middle
    return r, grouping


def find_best_grouping(Y, Tested_labels, k):
    indexes = [Tested_labels == i for i in range(k)]
    groupings_result = []
    for perm in itertools.permutations(range(k)):
        grouping = Tested_labels.copy()
        for i, p in enumerate(perm):
            grouping[indexes[i]] = p
        groupings_result.append(((grouping == Y).mean() * 100., grouping))
    return groupings_result[np.argmax([x[0] for x in groupings_result])][0]
