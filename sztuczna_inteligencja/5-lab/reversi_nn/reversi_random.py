#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
Losowy agent do Reversi.
'''
from __future__ import absolute_import
from __future__ import print_function
from __future__ import unicode_literals
from sklearn.neural_network import MLPClassifier
import pickle, copy, random, sys, operator
from reversiML import extractBonusAtributes
from engine_reversi import Reversi

# filename = "/home/kku/Documents/SI/5-lab/boards_weigths"
ADVANCED = True
filename = "/home/kku/Documents/SI/5-lab/reversi_nn/nn_advanced_atributes"


class Player(object):
    def __init__(self):
        self.reset()

    def reset(self):
        self.game = Reversi()
        self.my_player = 1
        self.say('RDY')

    def say(self, what):
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    def hear(self):
        line = sys.stdin.readline().split()
        return line[0], line[1:]

    def loop(self):
        self.nn = pickle.load(open(filename, 'rb'))
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                unused_move_timeout, unused_game_timeout = args[:2]
                move = tuple((int(m) for m in args[2:]))
                if move == (-1, -1):
                    move = None
                self.game.do_move(move, 1 - self.my_player)
            elif cmd == 'ONEMORE':
                self.reset()
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                assert not self.game.move_list
                self.my_player = 0

            moves = self.game.moves(self.my_player)
            if moves:
                # Kacper's Code
                move = self.chooseMove(moves)
                self.game.do_move(move, self.my_player)
            else:
                self.game.do_move(None, self.my_player)
                move = (-1, -1)
            self.say('IDO %d %d' % move)

    def chooseMove(self, moves):
        nextStates = []
        for m in moves:
            state = copy.deepcopy(self.game)
            state.do_move(m, self.my_player)
            codedBoard = []
            for i in range(self.game.M):
                for j in range(self.game.M):
                    if state.board[i][j] is None:
                        codedBoard.append(0)
                    elif state.board[i][j] == 0:
                        codedBoard.append(-1)
                    else:
                        codedBoard.append(1)
            if ADVANCED:
                codedBoard = extractBonusAtributes(codedBoard)
            nextStates.append(codedBoard)
        probabilities = [x[self.my_player]
                         for x in self.nn.predict_proba(nextStates)]
        index, value = max(enumerate(probabilities),
                           key=operator.itemgetter(1))
        return moves[index]


if __name__ == '__main__':
    player = Player()
    player.loop()
