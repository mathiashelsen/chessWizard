!zone Pawn

;; ARGUMENTS
currentPiece  = $50   ;; Pointer to the current piece

;; RETURN VALUE
move          = $52
score         = $54

;; WORK AREA
pieceCopy     = $60
moveDirection = $64
numberMoves   = $65   ;; Number of moves in that list
movesList     = $66   ;; Pointer to the list of moves+scores

getMoves:
  jsr .makeLocalCopy
  jsr .checkStrike
  jsr .checkMove
  rts

.makeLocalCopy
  ldy #$00
  lda (currentPiece),y
  sta pieceCopy
  iny
  lda (currentPiece),y
  sta pieceCopy+1
  iny
  lda (currentPiece),y
  sta pieceCopy+2
  iny
  lda (currentPiece),y
  sta pieceCopy+3
  lda currentPlayer
  sta moveDirection     ;; Black moves down, white moves up
  rts

;; Check if there is something on the diagonals
.checkStrike:

;; Check if the piece can move down/up
.checkMove:

;; Loop over all moves and only return the best one
.filterBest:
