*   = $c000

pieceList     = $1000
currentPlayer = pieceList+32*4+1
moveList      = currentPlayer+1

main:
  jsr initScreen
  jsr mainLoop

mainLoop:
  jmp mainLoop

!source "screen.s"

