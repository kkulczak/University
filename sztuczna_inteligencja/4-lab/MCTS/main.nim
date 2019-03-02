import engine
import mcts
import strutils
import sequtils
import math
import random
import os

#PARAMETERS!!!!!
const
  HOW_MANY_GAMES = 1

proc agentMinMax(state: gameState, player: int8, colorOfPlayer: int8): gameState =
  var moves: seq[gameState] = @[]
  for s in nextStates(state, player):
    moves.add(s)
  var bestIndex, bestValue = 0
  for i,m in moves:
    var tempVal = 0#alphabeta(m, DEEPTH_MIN_MAX ,low(int), high(int), -player, colorOfPlayer)
    if bestValue < tempVal:
      bestIndex = i
      bestValue = tempVal
  return moves[bestIndex]

proc playGame(): int =
  var player: int8 = 1
  var tab = getStartingBoard()
  while not terminal(tab):
    if player == 1:
      tab = agentMcts(tab, player)
      # tab = nextStates(tab, player).rand()
    else:
      var moves: seq[gameState] = @[]
      for s in nextStates(tab, player):
        moves.add(s)
      tab = moves.rand()
    player *= -1
    # var str = readLine(stdin)
    # printBoard(tab)
  return resultOfBoard(tab)

proc myMoveOnTorturament(state: var gameState, player: int8): gameState=
    var choosenNextState = agentMcts(state, player)
    for i in 0..SIZE:
      for j in 0..SIZE:
        if choosenNextState.board[i][j] != 0 and state.board[i][j] == 0:
          echo "IDO $1 $2" % [$i, $j]
          return choosenNextState
    echo "IDO -1 -1"
    return choosenNextState


proc playTorturament(): void =
  var myColor = 0'i8
  var tab : gameState = getStartingBoard()
  echo "RDY"
  while true:
    let data = readLine(stdin).split()
    case data[0]
    of "HEDID":
      if myColor == 0:
        myColor = -1
      var move = (parseInt(data[3]), parseInt(data[4]))
      if move == (-1,-1):
        tab.passedMoves += 1
      else:
        if tab.board[move[0]][move[1]] != 0:
          printBoard(tab)
          var e: ref OSError
          new(e)
          e.msg = "Iligal move!!! by enemy"
          raise e
        else:
          executeMove(tab.board, move[0], move[1], -myColor)
      tab = myMoveOnTorturament(tab, myColor)
    of "ONEMORE":
        myColor = 0
        tab = getStartingBoard()
        resetMcts()
        echo "RDY"
    of "BYE":
      break
    of "UGO":
      if myColor == 0:
        myColor = 1
      tab = myMoveOnTorturament(tab, myColor)
    # stderr.write(myColor)
    # stderr.write('\n')
    # printBoard(tab)


proc playRandm() : void =
  # randomize(1000)
  randomize()
  const games = HOW_MANY_GAMES
  var won = 0
  for x in 1..(games) :
    var resOfGame = playGame()
    if x mod 5 == 0:
      stdout.write('.')
      flushFile(stdout)
    if x mod 100 == 0 and x > 0:
      echo "$1 / $2 ".format(won, x)
    if resOfGame >= 0:
      won = won + 1
  echo "White won: $1 from $2 games".format(won, games)

if paramCount() >= 1 and paramStr(1) == "-t":
  playTorturament()
else:
  playRandm()

