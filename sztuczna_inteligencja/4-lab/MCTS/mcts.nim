import engine
import random
import sequtils
import math

type
  Node[T] = ref TNode[T]
  TNode[T] = object
    data: T
    parent: Node[T]
    children: seq[Node[T]]
  Wins = tuple[black, white: int]
  Color = range[-1..1]
  Mcts = object
    wins: Wins
    state: gameState

const
  c = 0.50
  MCTS_STEPS = 10000
var rootGlobal: Node[Mcts] #Node[Mcts](data: Mcts(wins: (0,0),state: getStartingBoard()), parent: nil, children: nil)

proc playRandomGame(fromState: gameState, nextMove: Color): int =
  var player: int8 = nextMove
  var tab = fromState
  while not terminal(tab):
    tab = toSeq(nextStates(tab, player)).rand()
    player *= -1
  return if resultOfBoard(tab) > 0: 1 else: -1

proc getWinsRatio(data: Wins, color: Color): float  =
  if  (float(data.white) + float(data.black)) == 0:
    return 0
  var wins: float = 0
  if color == -1:
    wins = float(data.black)
  elif color == 1:
    wins = float(data.white)
  return wins / (float(data.white) + float(data.black))

proc getGames(data:Wins): float =
  return float(data.black + data.white)

proc update(data: var Wins, whoWon: Color): void =
  if whoWon == -1:
    data.black += 1
  elif whoWon == 1:
    data.white += 1

proc chooseFromChildren(tab: seq[Node[Mcts]], time: int, color: Color) : Node[Mcts] =
  var
    bestIndex: seq[int] = @[]
    bestValue: float = 0
  for i, d in tab:
    var value : float = d.data.wins.getWinsRatio(color) +
      c * sqrt(ln(float(time)) / (d.data.wins.getGames() + 0.0001))
    if value == bestValue:
      bestIndex.add(i)
    elif value >= bestValue:
      bestIndex = @[i]
      bestValue = value
  return tab[bestIndex.rand()]

proc isLeaf(x: Node[Mcts]): bool =
  return x.children == nil



proc runMcts(root : Node[Mcts], steps: int, colorToWin: Color) : void =
  var
    node = root
  for time in 1..(steps):
    var color = colorToWin
    # FindLeaf
    while not node.isLeaf():
      node = node.children.chooseFromChildren(time, color)
      color *= -1
    # Expansion
    node.children = @[]
    for s in nextStates(node.data.state, color):
      node.children.add(
        Node[Mcts](
          data: Mcts(wins: (0,0), state:s),
          parent: node,
          children: nil
        )
      )
    # Simulation
    var wonGame = playRandomGame(node.data.state, color)
    # Backup
    while node.parent != nil:
      node.data.wins.update(wonGame)
      node = node.parent
  return

proc chooseStateAfterMcts(root: var Node[Mcts], colorToWin: Color) : gameState =
  var best: Node[Mcts] = root.children[0]
  for n in root.children:
    if n.data.wins.getWinsRatio(colorToWin) > best.data.wins.getWinsRatio(colorToWin) :
      best = n
  root = best
  best.parent = nil
  return best.data.state


proc agentMcts*(state: gameState, player: int8): gameState =
  if rootGlobal == nil:
    rootGlobal = Node[Mcts](data: Mcts(wins: (0,0),state: state), parent: nil, children: nil)
  else:
    var wasNewState = false
    for s in rootGlobal.children:
      if s.data.state.board == state.board:
        rootGlobal = s
        s.parent = nil
        wasNewState = true
        break
    if not wasNewState:
      printBoard(state)
      printBoard(rootGlobal.data.state)
      for s in rootGlobal.children:
        printBoard(s.data.state)
      var e: ref OSError
      new(e)
      e.msg = "MCTS Error - cant find new board"
      raise e

  rootGlobal.runMcts(MCTS_STEPS, player)
  return rootGlobal.chooseStateAfterMcts(player)

proc resetMcts*(): void =
  rootGlobal.children = nil
  rootGlobal.parent = nil
  rootGlobal = nil