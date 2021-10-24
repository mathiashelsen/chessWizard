#include "move.h"

void    deleteAllMoves(t_move* move)
{
  if(move->nextMove)
    deleteAllMoves(move->nextMove);

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
    move->from_y,
    move->to_x+'A',
    move->to_y);

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
      && board->pieces[squareIdx]->color == color
      && board->pieces[squareIdx]->type  == pawn )
    {
      searchResult = getAllPawnMoves(board, squareIdx);

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
