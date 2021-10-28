#include "minimax_engine.h"

t_move* minimaxEngine_getMove(t_board* board, t_color color, int plyDepth)
{
  t_move* move;
  t_move* moveIterator;
  t_move* bestMove;
  t_move* retVal;
  int     bestScore;
  int     score;
  move = getAllMoves(board, color);

  moveIterator  = move;
  bestMove      = NULL;
  bestScore     = -10000;

  while(moveIterator)
  {
    makeMove(board, moveIterator);

    score = minimaxRecAlgo(board, color, plyDepth-1);

    undoMove(board, moveIterator);

    if(score > bestScore && isMoveValid(board, moveIterator, color))
    {
      bestMove  = moveIterator;
      bestScore = score;
    }

    moveIterator = moveIterator->nextMove;
  }
  
  if(!bestMove)
  {
    printf("ERROR: Could not determine bestMove\n");
  }
  retVal  = malloc(sizeof(t_move));
  memcpy(retVal, bestMove, sizeof(t_move));

  deleteAllMoves(move);

  return retVal;
}

int     minimaxRecAlgo(t_board* board, t_color color, int plyDepth)
{
  t_move* allMoves;
  t_move* currentMove;
  int     bestScore;
  int     score;

  if(plyDepth == 0)
    return minimaxEngine_evaluateBoard(board, color);

  bestScore   = INT_MIN;
  score       = 0;
  allMoves    = NULL;
  allMoves    = getAllMoves(board, -color);
  currentMove = allMoves;

  while(currentMove)
  {
    makeMove(board, currentMove);

    score = -minimaxRecAlgo(board, -color, plyDepth-1); 
    if(score > bestScore)
      bestScore = score;

    undoMove(board, currentMove);

    currentMove = currentMove->nextMove;
  }

  deleteAllMoves(allMoves);
  return bestScore;
}

int     minimaxEngine_evaluateBoard(t_board* board, t_color color)
{
  int i;
  int score;
  int mul;


  score = 0;
  mul   = 1;

  for(i = 0; i < 64; i++)
  {
    if( board->pieces[i] )
    {
      if(board->pieces[i]->color == color)
        mul = 10;
      else
        mul = -10;

      switch(board->pieces[i]->type)
      {
        case pawn:    score += mul*1;
                      break;
        case knight:  score += mul*3;
                      break;
        case bishop:  score += mul*3;
                      break;
        case rook:    score += mul*5;
                      break;
        case queen:   score += mul*9;
                      break;
        case king:    score += mul*2;
                      break;
      }
    }
  }

  score += rand() % 10;

  return score;
}
