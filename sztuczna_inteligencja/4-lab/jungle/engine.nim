import random
import strutils
import algorithm
import math
import os

#PARAMETERS!!!!!
const
  SIZE_I = 8
  SIZE_J = 6
  MAX_PEACE_RUNDS = 50
  DEEPTH_MIN_MAX = 6
  HOW_MANY_GAMES = 1
var VERBOSE = false
type
  pos = tuple[x,y: int]
  row = array[0..SIZE_J, int8]
  board = array[0..SIZE_I, row]
  gameState = tuple[board: board, peaceRounds: int8]
const
  dirs: array[1..4, pos] = [(0, 1), (1, 0), (-1, 0), (0, -1)]
  swamp = 2
  trap = 3
  cave = 1
  enviroment: board = [ [0'i8, 0, 3, 1, 3, 0, 0],
                        [0'i8, 0, 0, 3, 0, 0, 0],
                        [0'i8, 0, 0, 0, 0, 0, 0],
                        [0'i8, 2, 2, 0, 2, 2, 0],
                        [0'i8, 2, 2, 0, 2, 2, 0],
                        [0'i8, 2, 2, 0, 2, 2, 0],
                        [0'i8, 0, 0, 0, 0, 0, 0],
                        [0'i8, 0, 0, 3, 0, 0, 0],
                        [0'i8, 0, 3,-1, 3, 0, 0]]

  startingBoard: board = [[7'i8, 0, 0, 0, 0, 0, 6],
                          [0'i8, 3, 0, 0, 0, 2, 0],
                          [1'i8, 0, 5, 0, 4, 0, 8],
                          [0'i8, 0, 0, 0, 0, 0, 0],
                          [0'i8, 0, 0, 0, 0, 0, 0],
                          [0'i8, 0, 0, 0, 0, 0, 0],
                          [-8'i8, 0, -4, 0, -5, 0, -1],
                          [0'i8, -3, 0, 0, 0, -2, 0],
                          [-6'i8, 0, 0, 0, 0, 0, -7]]


proc getSymbol(state: gameState, i: int, j: int) : char =
  case state.board[i][j]
  of  1: return 'R'
  of  2: return 'C'
  of  3: return 'D'
  of  4: return 'W'
  of  5: return 'J'
  of  6: return 'T'
  of  7: return 'L'
  of  8: return 'E'
  of -1: return 'r'
  of -2: return 'c'
  of -3: return 'd'
  of -4: return 'w'
  of -5: return 'j'
  of -6: return 't'
  of -7: return 'l'
  of -8: return 'e'
  of  0:
    case abs(enviroment[i][j]):
    of swamp: return '~'
    of trap: return '#'
    of cave: return '*'
    else: return '.'
  else: return '?'


proc printBoard(state: gameState): void =
  for i in 0..SIZE_I:
    for j in 0..SIZE_J:
      stderr.write(getSymbol(state, i ,j))
    stderr.write('\n')
  stderr.write("Peace Rounds: $1\n" % [$state.peaceRounds])
  stderr.write('\n')

proc isOnBoard(x:int ,y: int) : bool =
  let a = ((x >= 0) and (x <= SIZE_I) and (y >= 0) and (y <= SIZE_J))
  return a

proc isPlayerFigure(player: int8, fig: int8): bool =
  return player * fig > 0

proc getStartingBoard(): gameState =
  return (startingBoard, 1'i8)

proc terminal(state: gameState): bool =
  if abs(state.peaceRounds) >= MAX_PEACE_RUNDS or state.board[0][3] != 0 or state.board[8][3] != 0:
    return true
  var
    plus = 0
    minus = 0
  for x in state.board:
    for y in x:
      if y > 0:
        if minus != 0:
          return false
        plus += 1
      elif y < 0:
        if plus != 0:
          return false
        minus += 1
  return true

iterator nextStates(state:gameState, player: int8): gameState =
  var
    tab: board = state.board
  for x0 in 0..SIZE_I:
    for y0 in 0..SIZE_J:
      if not isPlayerFigure(player, tab[x0][y0]):
        continue
      let fig = tab[x0][y0]
      for d in dirs:
        var wasFight = false
        var
          x = x0 + d[0]
          y = y0 + d[1]
        if not isOnBoard(x,y):
          continue
        # Lew, Tygrys skacza przez stawy
        # Szcur wchodzi do wody
        if enviroment[x][y] == swamp:
          if not (abs(fig) in [1, 6, 7]):
            continue
          if abs(fig) in [6,7]:
            var isLegalJump = true
            while enviroment[x][y] == swamp:
              if tab[x][y] != 0:
                isLegalJump = false
                break
              x += d[0]
              y += d[1]
            if not isLegalJump:
              continue
        # Gracz nie moze wchodzic do wlasnej jamy.
        if enviroment[x][y] == player:
            continue
        #bicie

        if isPlayerFigure(player, tab[x][y]):
          continue

        if isPlayerFigure(-player, tab[x][y]):
          #wyjscie z wody
          if (enviroment[x0][y0] == swamp and enviroment[x][y] != swamp):
            continue
          # zanegowanie porpawnge bicia (w plapce lub normalnie lub slonia)
          if (enviroment[x][y] == trap or abs(tab[x][y]) <= abs(fig) or (abs(fig) == 1 and abs(tab[x][y]) == 8)):
            wasFight = true
          else:
            continue
        # executeMove
        tab[x][y] = fig
        tab[x0][y0] = 0
        yield (tab, if wasFight: player * 1'i8 else: player * (abs(state.peaceRounds) + 1'i8))
        tab = state.board

proc executeMove(state: var gameState,player: int8 ,xs: int, ys: int, xd: int, yd: int): void =
  var wasFight = false
  if xs != -1:
    if state.board[xd][yd] != 0:
      wasFight = true
    state.board[xd][ys] = state.board[xs][ys]
    state.board[xs][ys] = 0
  state.peaceRounds = if wasFight: player * 1'i8 else: player * (abs(state.peaceRounds) + 1'i8)

proc deductMove(oldState: gameState, newState: gameState): tuple[a,b,c,d: int] =
  var animal = -100
  var si, sj : int
  for i in 0..SIZE_I:
    for j in 0..SIZE_J:
      if oldState.board[i][j] != newState.board[i][j] and newState.board[i][j] == 0:
        animal = oldState.board[i][j]
        si = i
        sj = j
  for i in 0..SIZE_I:
    for j in 0..SIZE_J:
      if newState.board[i][j] == animal:
        return (si, sj, i ,j)
  return (-1,-1,-1,-1)


proc resultOfBoard(state: gameState): int =
  var tab = state.board
  # cave entrance
  if tab[0][3] < 0:
    return -1
  if tab[8][3] > 0:
    return +1
  # best animal on board
  var
    bestPlus = 0
    bestMinus = 0
  for i in 0..SIZE_I:
    for j in 0..SIZE_J:
      bestPlus = max(bestPlus, tab[i][j])
      bestMinus = min(bestMinus, tab[i][j])
  if abs(bestMinus) > bestPlus:
    return -1
  elif bestPlus > abs(bestMinus):
    return +1
  # taxi distances
  var
    minusDists: seq[int] = @[]
    plusDists: seq[int] = @[]
  for i in 0..SIZE_I:
    for j in 0..SIZE_J:
      if tab[i][j] > 0:
        plusDists.add( abs(i - 8) + abs(j - 3))
      elif tab[i][j] < 0:
        minusDists.add( abs(i - 0) + abs(j - 3))
  sort(minusDists, system.cmp[int])
  sort(plusDists, system.cmp[int])
  for i in 0..min(len(plusDists) - 1, len(minusDists) - 1):
    if plusDists[i] < minusDists[i]:
      return -1
    if minusDists[i] < plusDists[i]:
      return +1
  # last move
  return if state.peaceRounds > 0: +1 else: -1


proc hValue(state: gameState, player: int8): int =
  if VERBOSE:
    printBoard(state)
  var
    res = 0
    taxis: seq[int] = @[]
  for i in 0..SIZE_I:
    for j in 0..SIZE_J:
      res += state.board[i][j] * player
      if isPlayerFigure(player, state.board[i][j]):
        taxis.add(abs(i - (if player < 0: 0 else: 8)) + abs(j - 3))
  if VERBOSE:
    echo taxis
  res += (10 - min(taxis)) * 4
  return res


proc alphabeta(node: gameState, depth: int, alpha0: int, beta0: int, color: int8, colorOfPlayer: int) : int =
    if terminal(node):
      return resultOfBoard(node) * 10000 * colorOfPlayer
    if depth <= 0:
      return hValue(node, int8(colorOfPlayer))
    var
      alpha = alpha0
      beta = beta0
      v: int

    if color == 1:
      v = low(int)
      for child in nextStates(node, color):
        v = max(v,  alphabeta(child, depth - 1, alpha, beta, -color, colorOfPlayer))
        alpha = max(alpha, v)
        if beta <= alpha:
          break
    else:
      v = high(int)
      for child in nextStates(node, color):
        v = min(v,  alphabeta(child, depth - 1, alpha, beta, -color, colorOfPlayer))
        beta = min(beta, v)
        if beta <= alpha:
          break
    return v

proc agentMinMax(state: gameState, player: int8, colorOfPlayer: int8): gameState =
  var moves: seq[gameState] = @[]
  for s in nextStates(state, player):
    moves.add(s)
  var bestIndex, bestValue = 0
  for i,m in moves:
    var tempVal = alphabeta(m, DEEPTH_MIN_MAX ,low(int), high(int), -player, colorOfPlayer)
    if bestValue < tempVal:
      bestIndex = i
      bestValue = tempVal
  return moves[bestIndex]

proc playGame(): int =
  var player: int8 = 1
  var tab = getStartingBoard()
  if VERBOSE:
    printBoard(tab)
  while not terminal(tab):
    if player == 1:
      tab = agentMinMax(tab, player, player)
    else:
      var moves: seq[gameState] = @[]
      for s in nextStates(tab, player):
        moves.add(s)
      tab = moves.rand()
    player *= -1
    if VERBOSE:
      printBoard(tab)
      var x = readline(stdin)
  return resultOfBoard(tab)


proc playRandm() : void =
  randomize(3849)
  # randomize()
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

proc playTorturament() : void =
  var
    player: int8
    state : gameState

  proc say(what: string): void =
    stdout.writeLine(what)
    flushFile(stdout)

  proc reset() : void =
    state = getStartingBoard()
    player = 1'i8
    say("RDY")

  proc hear(): tuple[cmd:string, line: seq[string]] =
    var line = readLine(stdin).split()
    return (line[0], line)

  reset()
  while true:
    var (cmd, data) = hear()
    if cmd == "HEDID":
      let
        xs = parseInt(data[4])
        ys = parseInt(data[3])
        xd = parseInt(data[6])
        yd = parseInt(data[5])
      executeMove(state, -player, xs, ys, xd, yd)
    elif cmd == "ONEMORE":
      reset()
      continue
    elif cmd == "BYE":
      break
    elif cmd == "UGO":
      player = -1
    if VERBOSE:
      printBoard(state)
    var newState = agentMinMax(state, player, player)
    var move = deductMove(state, newState)
    state = newState
    if VERBOSE:
      printBoard(state)
    say("IDO $1 $2 $3 $4" % [$move[1], $move[0], $move[3], $move[2]])




if paramCount() >= 1 and paramStr(1) == "-t":
  playTorturament()
else:
  VERBOSE = true
  var state: gameState = getStartingBoard()
  state.board[6][1] = -8
  state.board[6][0] = 0
  # printBoard(state)
  # for s in nextStates(state, 1):
  #   printBoard(s)
  echo hValue(state, -1)
  # playRandm()