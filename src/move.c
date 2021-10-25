#include "move.h"

void    deleteAllMoves(t_move* move)
{
  if(  move
    && move->nextMove)
    deleteAllMoves(move->nextMove);

  if(  move )
    free(move);
}

t_move* getLastMove(t_move* move)
{
  if(move->nextMove)
    return getLastMove(move->nextMove);
  else
    return move;
}

void    printAllMoves(t_board* board, t_move* move)
{
  t_piece* piece = board->pieces[move->from_x + 8*move->from_y];
  printf("Move %s from %c%d to %c%d\n", 
    getPieceName(piece),
    move->from_x+'A',
    move->from_y+1,
    move->to_x+'A',
    move->to_y+1);

  if(move->nextMove)
    printAllMoves(board, move->nextMove);
}

void    concatenateMovesList(t_move* listA, t_move* listB)
{
  t_move* finalNodeA    = getLastMove(listA);
  finalNodeA->nextMove  = listB;
}

t_move* getAllMoves(t_board* board, t_color color)
{
  char    squareIdx;
  t_move* movesList;
  t_move* searchResult;

  movesList = NULL;

  for(squareIdx = 0; squareIdx < 63; squareIdx++)
  {
    
    if(  board->pieces[squareIdx] 
      && board->pieces[squareIdx]->color == color)
    {
      switch(board->pieces[squareIdx]->type)
      {
        case(pawn):   searchResult = getAllPawnMoves    (board, squareIdx);
                      break;
        case(king):   searchResult = getAllKingMoves    (board, squareIdx);
                      break;
        case(knight): searchResult = getAllKnightMoves  (board, squareIdx);
                      break;
        case(rook):   searchResult = getAllRookMoves    (board, squareIdx);
                      break;
        case(bishop): searchResult = getAllBishopMoves  (board, squareIdx);
                      break;
        case(queen):  searchResult = getAllQueenMoves   (board, squareIdx);
                      break;
        default:      searchResult = NULL;
                      break;
      }

      if(!movesList)
        movesList = searchResult;
      else
        concatenateMovesList(movesList, searchResult);
    }
  }

  return movesList;
}

/*
 * For a pawn at position squareIdx, this will return
 * all possible moves.
 */
t_move* getAllPawnMoves(t_board* board, char squareIdx)
{
  t_piece*  piece;
  t_piece*  pieceUnderAttack;
  t_move*   move;
  t_move*   nextMove;
  char      pieceX;
  char      pieceY;

  piece     = board->pieces[squareIdx];
  move      = NULL;
  nextMove  = NULL;

  pieceX    = squareIdx % 8;
  pieceY    = squareIdx / 8;

  if( !pieceAt(board, pieceX, pieceY + piece->color))
  {
    if( (pieceY+piece->color) > -1 && (pieceY+piece->color) < 8)
    {
      move                = malloc(sizeof(t_move));
      move->from_x        = pieceX;
      move->from_y        = pieceY;
      move->to_x          = pieceX;
      move->to_y          = pieceY + piece->color; 
      move->moveType      = quiet;
      move->capturedPiece = NULL;
      move->nextMove      = NULL;
    }
  }
  
  if( (piece->color == white && pieceY == 1) || (piece->color == black && pieceY == 6))
  {
    if( !pieceAt(board, pieceX, pieceY+2*piece->color) )
    {
      if(pieceY+2*piece->color > -1 && pieceY+2*piece->color < 8)
      {
        nextMove                = malloc(sizeof(t_move));
        nextMove->from_x        = pieceX;
        nextMove->from_y        = pieceY;
        nextMove->to_x          = pieceX;
        nextMove->to_y          = pieceY + 2*piece->color;
        nextMove->nextMove      = move;
        nextMove->moveType      = quiet;
        nextMove->capturedPiece = NULL;

        move                    = nextMove;
      }
    }
  }
  
  pieceUnderAttack = pieceAt(board, pieceX+1, pieceY+piece->color);
  if(  pieceUnderAttack
    && pieceUnderAttack->color == - piece->color )
  {
        nextMove                = malloc(sizeof(t_move));
        nextMove->from_x        = pieceX;
        nextMove->from_y        = pieceY;
        nextMove->to_x          = pieceX+1;
        nextMove->to_y          = pieceY + piece->color;
        nextMove->nextMove      = move;
        nextMove->moveType      = capture;
        nextMove->capturedPiece = pieceUnderAttack; 

        move                    = nextMove;
    
  }

  pieceUnderAttack = pieceAt(board, pieceX-1, pieceY+piece->color);
  if(  pieceUnderAttack
    && pieceUnderAttack->color == - piece->color )
  {
        nextMove                = malloc(sizeof(t_move));
        nextMove->from_x        = pieceX;
        nextMove->from_y        = pieceY;
        nextMove->to_x          = pieceX-1;
        nextMove->to_y          = pieceY + piece->color;
        nextMove->nextMove      = move;
        nextMove->moveType      = capture;
        nextMove->capturedPiece = pieceUnderAttack; 

        move                    = nextMove;
    
  }

  return move;
}

t_move* getAllKingMoves(t_board* board, char squareIdx)
{
  // Points to the last move made
  t_move*   move;
  // To allocate a new move
  t_move*   newMove;
  t_piece*  piece = board->pieces[squareIdx];

  char i;
  char x = squareIdx % 8;
  char y = squareIdx / 8;

  char dir[8][2] = {
    {+1,  0},
    {+1, +1},
    {0 , +1},
    {-1, +1},
    {-1,  0},
    {-1, -1},
    { 0, -1},
    {+1, -1}
  };

  move = NULL;
  for(i = 0; i < 8; i++)
  {
    if(isMovePseudoValid(board, x+dir[i][0], y+dir[i][1], piece->color))
    {
      newMove = malloc(sizeof(t_move));
      newMove->from_x = x;
      newMove->from_y = y;
      newMove->to_x   = x+dir[i][0];
      newMove->to_y   = y+dir[i][1];
      newMove->capturedPiece = board->pieces[newMove->to_x + 8*newMove->to_y];

      newMove->nextMove = move;
      move              = newMove;
    }
  }

  return move;
}


t_move* getAllKnightMoves(t_board* board, char squareIdx)
{
  // Points to the last move made
  t_move*   move;
  // To allocate a new move
  t_move*   newMove;
  t_piece*  piece = board->pieces[squareIdx];

  char i;
  char x = squareIdx % 8;
  char y = squareIdx / 8;

  char dir[8][2] = {
    {+1, +2},
    {+1, -2},
    {-1, +2},
    {-1, -2},
    {+2, +1},
    {+2, -1},
    {-2, +1},
    {-2, -1}
  };

  move = NULL;
  for(i = 0; i < 8; i++)
  {
    if(isMovePseudoValid(board, x+dir[i][0], y+dir[i][1], piece->color))
    {
      newMove = malloc(sizeof(t_move));
      newMove->from_x = x;
      newMove->from_y = y;
      newMove->to_x   = x+dir[i][0];
      newMove->to_y   = y+dir[i][1];
      newMove->capturedPiece = board->pieces[newMove->to_x + 8*newMove->to_y];

      newMove->nextMove = move;
      move              = newMove;
    }
  }

  return move;
}

t_move* getAllRookMoves(t_board* board, char pieceIdx)
{
  char i;
  t_move* move;
  t_move* newMove;

  move    = NULL;

  char dir[4][2] = {
    { 1,  0},
    {-1,  0},
    { 0,  1},
    { 0, -1}
  };

  for(i = 0; i < 4; i++)
  {
    newMove = getLinearStepMoves(board, pieceIdx, dir[i][0], dir[i][1]);
    if(move)
      concatenateMovesList(move, newMove);
    else
      move = newMove;
  }
  return move;
}

t_move* getAllBishopMoves (t_board* board, char pieceIdx)
{
  char i;
  t_move* move;
  t_move* newMove;

  move    = NULL;

  char dir[4][2] = {
    { 1,  1},
    {-1,  1},
    { 1, -1},
    {-1, -1}
  };

  for(i = 0; i < 4; i++)
  {
    newMove = getLinearStepMoves(board, pieceIdx, dir[i][0], dir[i][1]);
    if(move)
      concatenateMovesList(move, newMove);
    else
      move = newMove;
  }
  return move;

}

t_move* getAllQueenMoves (t_board* board, char pieceIdx)
{
  char i;
  t_move* move;
  t_move* newMove;

  move    = NULL;

  char dir[8][2] = {
    { 1,  1},
    {-1,  1},
    { 1, -1},
    {-1, -1},
    { 1,  0},
    {-1,  0},
    { 0,  1},
    { 0, -1}
  };

  for(i = 0; i < 8; i++)
  {
    newMove = getLinearStepMoves(board, pieceIdx, dir[i][0], dir[i][1]);
    if(move)
      concatenateMovesList(move, newMove);
    else
      move = newMove;
  }
  return move;

}

t_move* getLinearStepMoves(t_board* board, char pieceIdx, char x_step, char y_step)
{
  char    x_start, y_start, x, y;
  t_move* move;
  t_move* newMove;
  t_piece* piece;

  piece   = board->pieces[pieceIdx];
  move    = NULL;
  x       = pieceIdx % 8;
  y       = pieceIdx / 8;
  x_start = x;
  y_start = y;

  x       = x + x_step;
  y       = y + y_step;

  while(isMovePseudoValid(board, x, y, piece->color) == 1)
  {
    newMove = malloc(sizeof(t_move));
    newMove->from_x = x_start;
    newMove->from_y = y_start;
    newMove->to_x   = x;
    newMove->to_y   = y;
    newMove->capturedPiece = NULL;

    newMove -> nextMove = move;
    move                = newMove;
    x                   = x + x_step;
    y                   = y + y_step;
  }

  if(isMovePseudoValid(board, x, y, piece->color) == 2)
  {
    newMove = malloc(sizeof(t_move));
    newMove->from_x = x_start;
    newMove->from_y = y_start;
    newMove->to_x   = x;
    newMove->to_y   = y;
    newMove->capturedPiece = board->pieces[x + 8*y];

    newMove -> nextMove = move;
    move                = newMove;
  }

  return move;
}

void  makeMove(t_board* board, t_move* move)
{
  if(move)
  {
    board->pieces[move->to_x + 8*move->to_y] = 
      board->pieces[move->from_x + 8*move->from_y];
    
    board->pieces[move->from_x + 8*move->from_y] = NULL;
    // Promotion, castling etc also goes here
  }
}

void  undoMove(t_board* board, t_move* move)
{
  if(move)
  {
    board->pieces[move->from_x + 8*move->from_y] =
      board->pieces[move->to_x + 8*move->to_y];

    // Captured piece could be a null pointer, which is still valid
    board->pieces[move->to_x + 8*move->to_y] = move->capturedPiece;

    // Should also check for promotion, castling, etc.
  }
}

char  isMovePseudoValid(t_board* board, char x, char y, t_color color)
{
  if(x > -1 && x < 8 && y > -1 && y < 8)
  {
    // There is no piece at the specified location
    if(!pieceAt(board, x, y))
      return 1; 
    // There is a piece, and we can capture it
    else if( pieceAt(board, x, y)->color != color) 
      //Valid, but stop a possible loop
      return 2;
    // There is a piece, but we can't capture it
    else
      return 0;
  }
  else
  {
    return 0;
  }
}

char  isMoveValid(t_board* board, t_move* move, t_color color)
{
  char valid;
  makeMove(board, move);


  if(isKingUnderAttack(board, color))
    valid = 0;
  else
    valid = 1;

  undoMove(board, move);

  return valid;
}

char  isKingUnderAttack(t_board* board, t_color color)
{
  char retVal;
  t_move* move;
  t_move* LL_root;
  
  retVal = 0;

  move    = getAllMoves(board, color*-1);
  LL_root = move;

  while(move)
  {
    if(  move->capturedPiece
      && move->capturedPiece->color == color
      && move->capturedPiece->type  == king 
    )
    {
        retVal++;
        move = NULL;
    }
    else
    {
      move = move->nextMove;
    }
  }

  deleteAllMoves(LL_root);
  return retVal;
}

char  isCheckmate(t_board* board, t_color color)
{
  t_move* move;
  t_move* LL_root;

  move    = getAllMoves(board, color);
  LL_root = move;

  // Keep looking for other moves, if this one is invalid
  while(move
    && !isMoveValid(board, move, color))
  {
    move = move->nextMove;
  }

  deleteAllMoves(LL_root);

  if(move)
    return 0;
  else
    return 1;
}
