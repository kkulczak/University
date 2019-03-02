import numpy as np
import scipy
from sklearn.model_selection import (train_test_split, KFold)
from sklearn import metrics

class KNN():
    def __init__(self, k=3):
        self.k = k

    def fit(self, X_train, Y_train):
        self.X_train = X_train
        self.Y_train = Y_train

    def score(self, X, target):
        # a = np.sum(X ** 2, axis=1)
        b = np.sum(self.X_train ** 2, axis=1)
        c = -2 * (X @ self.X_train.T)
        distances = (
            c + b + a[:, np.newaxis]
        )
        ids = np.argsort(distances, axis=1)[:, :self.k]
        labels = self.Y_train[ids]
        return (
            scipy.stats.mode(labels, axis=1).mode.reshape(-1) == target
        ).mean()


def score_model_with_split(model, X, Y, test_size=0.25):
    X_train, X_test, Y_train, Y_test = train_test_split(
        X,
        Y,
        test_size=test_size
    )
    model.fit(X_train, Y_train)
    print(metrics.confusion_matrix(model.predict(X_test), Y_test))
    
    return model.score(X_test, Y_test)

# def score_confusion_matrix(model, X, Y, test_size=0.25):
#     X_train, X_test, Y_train, Y_test = train_test_split(
#         X,
#         Y,
#         test_size=test_size
#     )
#     model.fit(X_train, Y_train)
#     return metrics.confusion_matrix(model.predict(X_test), Y_test)


def score_model_with_cross_validation(model, X, y, n_splits=10):
    scores = np.zeros(n_splits)
    kf = KFold(n_splits=n_splits, shuffle=True)
    for i, (train_index, test_index) in enumerate(kf.split(X)):
        X_train, X_test = X[train_index], X[test_index]
        y_train, y_test = y[train_index], y[test_index]

        model.fit(X_train, y_train)

        scores[i] = model.score(X_test, y_test)
    return scores.mean()
