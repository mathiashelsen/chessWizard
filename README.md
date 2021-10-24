# chessWizard
A Chess Game (for the C64, but not really, because too difficult) Anyhow, the thing plays better chess than me...

# Algorithm overview
```
  board = initializeBoard();

  while(board.valid())
  {
    if(player)
      move = engine.getMove(board);
    else
      move = human.getMove(board);

    board.makeMove(move)
    player = ~player;
  }
```

The stop condition is to check for check mate
```
  board.valid(): Check for check mate
    for all piece of opposite player:
      scores, moves = piece.getAllMoves()
      // Check if the move would place the opposer at the kings position
      if(move == board.piece[king])
        return false
    return true
```

After a move has been made, the board has to be updated
```
  board.makeMove(move): Update the piece list:
    1) move the piece
    2) possibly eliminate an opposing piece
    3) possibly move another piece (castling)
    4) possibly swap the original piece (pawn to queen)
```

The most tricky thing is ofcourse the engine implementation. Probably
best to start with a simple greedy or random engine.
Greedy algo:
```
  engine.getMove(board):
    bestScore = -1
    for all piece of player:
      scores, moves = piece.getAllMoves()
      // Score can be calculated from the board/move, not from getAllMoves
      for all move of moves:
        if(score > bestScore && move == valid)
          bestMove = move
      return bestMove
```
We thus also need an algorithm to check if a move is valid. If no valid moves are available,
the player is checkmate. A move is valid if the king is not under attack.

Random algo:
```
  engine.getMove(board):
    piece_idx = rand(0..15)
    looking   = true
    while(looking)
      if(board[piece_idx] == active)
        moves = board[piece_idx].getAllMoves();
        if(moves != NULL)
          return moves[rand(0..length(moves)-1)]
      piece_idx = rand(0..15)
```

Which boils down to the fact that we need a function:
```
  piece.getAllMoves():
    switch(piece)
      case(pawn):
        possible: move 1 forward (stop before any)
        possible: move 2 forward (stop before any)
        possible: capture to side (x2)
        possible: capture en-passant (x2)
      case(rook):
        possible: move N  (stop at other, stop before own)
        possible: move E  (stop at other, stop before own)
        possible: move S  (stop at other, stop before own)
        possible: move W  (stop at other, stop before own)
      case(bishop):
        possible: move NE (stop at other, stop before own)
        possible: move NW (stop at other, stop before own)
        possible: move SE (stop at other, stop before own)
        possible: move SW (stop at other, stop before own)
      case(knight):
        possible: move {+/-2, +/-1} (stop at other, stop before own)
        possible: move {+/-1, +/-2} (stop at other, stop before own)
      case(queen)
        ...
      case(king)
        ...
```
However, this function does not filter if we would place ourselves checkmate.
As such, it needs to call board.valid with the suggested move. The move has
to be discarded if it would invalidate the position.

