import sequtils
import os

const
  LOOP = 300
  GAMMA = 0.99
  LOOSE = -100.0
  STEP_REWARD = -0.1
  X_SIZE = 25
  Y_SIZE = 82
type
  Data = tuple[x,y: int8, val: float]
  Speeds = array[-3..3, array[-3..3, Data]]
  Board = array[0..LOOP, array[0..X_SIZE, array[0..Y_SIZE, Speeds]]]

var route: seq[seq[char]] = @[]
var tab: Board
var line = readLine(stdin)
var start = (0,0)

while line != "" and line != "\n":
  route.add(toSeq(line.items()))
  line = (readLine(stdin))



proc nextState(state: tuple[x,y,vx,vy: int], action: tuple[dx,dy: int]) : tuple[nx,ny,nvx,nvy: int] =
  var (x, y, vx, vy) = state
  var (dvx, dvy) = action  # (*)
  vx += dvx
  vy += dvy

  if vx > 3:
      vx = 3
  if vy > 3:
      vy = 3
  if vx < -3:
      vx = -3
  if vy < -3:
      vy = -3
  x += vx
  y += vy
  return (x,y,vx,vy)


proc isInBoard(x:int,y:int) : bool =
  return x >= 0 and x < route.len() and y >= 0 and y < route[0].len()


for i in 1..LOOP:
  for x in 0..route.len()-1:
    for y in 0..route[0].len()-1:
      for vx in -3..3:
        for vy in -3..3:
          for dx in -1..1:
            for dy in -1..1:
              if route[x][y] == 's':
                start = (x,y)
              if route[x][y] == '.':
                tab[i][x][y][vx][vy].val = LOOSE
              elif route[x][y] == 'e':
                tab[i][x][y][vx][vy].val = 100.0

for i in 1..LOOP:
  stderr.writeLine(tab[i-1][start[0]][start[1]][0][0].val)
  for x in 0..route.len()-1:
    for y in 0..route[0].len()-1:
      for vx in -3..3:
        for vy in -3..3:
          if route[x][y] == '.':
            tab[i][x][y][vx][vy].val = LOOSE
            continue
          if route[x][y] == 'e':
            tab[i][x][y][vx][vy].val = 100.0
            continue
          var bestAction: Data = (0'i8, 0'i8, low(float))
          for dx in -1..1:
            for dy in -1..1:
              var (nx, ny, nvx, nvy) = nextState((x,y,vx,vy), (dx,dy))
              var value = 0.0
              if route[x][y] != 'o':
                if isInBoard(nx,ny):
                  value += STEP_REWARD + GAMMA * tab[i-1][nx][ny][nvx][nvy].val
                else:
                  value += STEP_REWARD + GAMMA * LOOSE
              else:
                for odx in -1..1:
                  for ody in -1..1:
                    var (nx, ny, nvx, nvy) = nextState((x,y,vx,vy), (dx + odx,dy + ody))
                    if isInBoard(nx,ny):
                      value += STEP_REWARD + GAMMA * tab[i-1][nx][ny][nvx][nvy].val
                    else:
                      value += STEP_REWARD + GAMMA * LOOSE
                    value = value / 9.0
              if bestAction.val < value:
                bestAction = (int8(dx), int8(dy), value)
          tab[i][x][y][vx][vy] = bestAction


for x in 0..route.len()-1:
  for y in 0..route[0].len()-1:
    for vx in -3..3:
      for vy in -3..3:
        if route[x][y] == '.':
          continue
        echo y, " ", x, " ", vy, " ", vx, " ", tab[LOOP][x][y][vx][vy].y, " ", tab[LOOP][x][y][vx][vy].x