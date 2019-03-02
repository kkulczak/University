import random
import strutils
import math
import os

#PARAMETERS!!!!!
const
  SIZE = 7
  DEEPTH_MIN_MAX = 8
  HOW_MANY_GAMES = 1
  dirs: array[0..7, tuple[x: int, y: int]] = [(0, 1), (1, 0), (-1, 0), (0, -1), (1, 1), (-1, -1), (1, -1), (-1, 1)]
type
  row = array[0..SIZE, int8]
  board = array[0..SIZE, row]
  gameState = tuple[board: board, passedMoves: int8]

proc getStartingBoard(): gameState =
  var tab: board
  tab[3][3] = -1
  tab[3][4] = 1
  tab[4][3] = 1
  tab[4][4] = -1
  return (tab, 0'i8)

proc printBoard(state: gameState): void =
  for x in state.board:
    for y in x:
      if y == 0:
        stderr.write('.')
      elif y == 1:
        stderr.write('O')
      elif y == -1:
        stderr.write('#')
    stderr.write('\n')
  stderr.write('\n')

proc isOnBoard(x:int ,y: int)  : bool {.inline.}  =
  let a = ((x >= 0) and (x <= SIZE) and (y >= 0) and (y <= SIZE))
  return a

proc executeMove(tab: var board, x0: int, y0: int, player: int8) =
  for d in dirs:
        var
          (dx ,dy) = d
          x = x0 + dx
          y = y0 + dy
          to_beat = 0
        while isOnBoard(x,y) and tab[x][y] == -player:
          x += dx
          y += dy
          to_beat += 1
        if to_beat > 0 and isOnBoard(x,y) and tab[x][y] == player:
          x = x0
          y = y0
          for nums in 0..(to_beat+1):
            tab[x][y] = player
            x += dx
            y += dy

proc terminal(state: gameState): bool {.inline.} =
  if state.passedMoves >= 2:
    return true
  for x in 0..SIZE:
    for y in 0..SIZE:
      if state.board[x][y] == 0:
        return false
  return true

iterator nextStates(state:gameState, player: int8): gameState =
  var
    tab: board = state.board
    res: int = 0
  for x0 in 0..SIZE:
    for y0 in 0..SIZE:
      var madeMove = false
      if tab[x0][y0] != 0:
        continue
      # printBoard(tab)
      for d in dirs:
        var
          (dx ,dy) = d
          x = x0 + dx
          y = y0 + dy
          to_beat = 0
        while isOnBoard(x,y) and tab[x][y] == -player:
          x += dx
          y += dy
          to_beat += 1
        if to_beat > 0 and isOnBoard(x,y) and tab[x][y] == player:
          x = x0
          y = y0
          for nums in 0..(to_beat+1):
            madeMove = true
            tab[x][y] = player
            x += dx
            y += dy
      if madeMove:
        yield (tab, 0'i8)
        tab = state.board
        res += 1
  if res == 0:
    yield (tab, state.passedMoves + 1'i8)

proc resultOfBoard(state: gameState): int =
  var res = 0
  for x in 0..SIZE:
    for y in 0..SIZE:
      res = res + state.board[x][y]
  return res

const C = 4'i8
const N = -3'i8
const M = -4'i8
const J = 1'i8
const B = 2'i8
const hArray: board = [ [ C , N , B , B , B , B , N, C],
                        [ N , M , -J , -J , -J , -J , M, N],
                        [ B , -J , J , 0 , 0 , J , -J , B],
                        [ B , -J , 0 , J , J , 0 , -J , B],
                        [ B , -J , 0 , J , J , 0 , -J , B],
                        [ B , -J , J , 0 , 0 , J , -J , B],
                        [ N , M , -J , -J , -J , -J , M, N],
                        [ C , N , B , B , B , B , N, C]
                        ]

proc hValueArr(state: gameState) : int  =
  var res = 0
  for i in 0..SIZE:
    for j in 0..SIZE:
      res += hArray[i][j] * state.board[i][j]
  return res


proc hValueCorners(state: gameState) : int  =
  const
    corner: int = 10
    neibghour: int = 5
  var
    res: int = 0
  res += state.board[0][0] * 10
  res += state.board[7][0] * corner
  res += state.board[7][7] * corner
  res += state.board[0][7] * corner
  if state.board[0][0] != 0: res += (state.board[0][1] + state.board[1][0] + state.board[1][1]) * neibghour
  if state.board[7][0] != 0: res += (state.board[6][0] + state.board[6][1] + state.board[7][1]) * neibghour
  if state.board[0][7] != 0: res += (state.board[0][6] + state.board[1][6] + state.board[1][7]) * neibghour
  if state.board[7][7] != 0: res += (state.board[6][7] + state.board[6][6] + state.board[7][6]) * neibghour
  return res

proc alphabeta(node: gameState, depth: int, alpha0: int, beta0: int, color: int8, colorOfPlayer: int) : int =
    if terminal(node):
      let gRes = if resultOfBoard(node) >= 0: 1 else: -1
      return  gRes * 10000 * colorOfPlayer
    if depth <= 0:
      return hValueArr(node) * colorOfPlayer
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
  while not terminal(tab):
    if player == 1:
      tab = agentMinMax(tab, player, player)
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
    var choosenNextState = agentMinMax(state, player, player)
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