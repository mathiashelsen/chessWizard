*   = $c000

pieceList     = $1000
currentPlayer = pieceList+32*4+1
moveList      = currentPlayer+1

main:
  jsr initScreen
  jsr mainLoop

mainLoop:
  lda #$01
  sta $6800
  lda #$02
  sta $6801
  jmp mainLoop

!source "screen.s"

