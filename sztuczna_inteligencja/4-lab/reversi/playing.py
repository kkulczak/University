from reversi_engine import Board, Black
from main import *


def hashFromBoard(board):
    return tuple([tuple(x) for x in board])


def play(playerFunction, weigthMatrix=False):
    B = Board()

    while True:
        if B.player == Black:
            m = B.random_move()
        else:
            m = playerFunction(B)
        B.do_move(m)
        if B.terminal():
            break
        # print(B.show(), B.fields)
    return B.result(gameEnded=True)

def negamax(node, depth, α, β, color):
    if depth = 0 or node is a terminal node
        return color * the heuristic value of node
    childNodes = GenerateMoves(node)
    childNodes = OrderMoves(childNodes)
    bestValue = −∞
    foreach child in childNodes
        v = −negamax(child, depth − 1, −β, −α, −color)
        bestValue = max( bestValue, v )
        α = max( α, v )
        if α >= β
            break
    return bestValue

def max_value(state, alpha, beta, level):
    if state.terminal():
        return state.result()
    if level <= 0:
        return state.result()
    value = -float("inf")

    for a in state.moves():
        state.do_move(a)
        value = max(value, min_value(state, alpha, beta, level - 1))
        state.revertMove()
        if value >= beta:
            return value
        alpha = max(alpha, value)
    return value


def min_value(state, alpha, beta, level):
    if state.terminal():
        return state.result()
    if level <= 0:
        return state.result()
    value = float("inf")

    for a in state.moves():
        state.do_move(a)
        value = min(value, max_value(state, alpha, beta, level - 1))
        state.revertMove()
        if value <= alpha:
            return value
        beta = min(beta, value)
    return value


def BasicPlayer(board):
    movesWithValues = []
    for m in board.moves():
        board.do_move(m)
        value = min_value(board, -float("inf"), float("inf"), 3)
        movesWithValues.append((
            value,
            m
        ))
        board.revertMove()
    return max(movesWithValues)[1]
