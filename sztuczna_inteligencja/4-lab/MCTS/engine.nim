const
  SIZE* = 7
  dirs*: array[0..7, tuple[x: int, y: int]] = [(0, 1), (1, 0), (-1, 0), (0, -1), (1, 1), (-1, -1), (1, -1), (-1, 1)]
type
  row* = array[0..SIZE, int8]
  board* = array[0..SIZE, row]
  gameState* = tuple[board: board, passedMoves: int8]

proc getStartingBoard*(): gameState =
  var tab: board
  tab[3][3] = -1
  tab[3][4] = 1
  tab[4][3] = 1
  tab[4][4] = -1
  return (tab, 0'i8)

proc printBoard*(state: gameState): void =
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

proc executeMove*(tab: var board, x0: int, y0: int, player: int8) =
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

proc terminal*(state: gameState): bool {.inline.} =
  if state.passedMoves >= 2:
    return true
  for x in 0..SIZE:
    for y in 0..SIZE:
      if state.board[x][y] == 0:
        return false
  return true

iterator nextStates*(state:gameState, player: int8): gameState =
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

proc resultOfBoard*(state: gameState): int =
  var res = 0
  for x in 0..SIZE:
    for y in 0..SIZE:
      res = res + state.board[x][y]
  return res
