#include "greedy_engine.h"

t_move* greedyEngine_getMove(t_board* board, t_color color)
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
  bestScore     = -1;

  while(moveIterator)
  {
    makeMove(board, moveIterator);

    score = greedyEngine_evaluateBoard(board, color); 

    undoMove(board, moveIterator);

    if(score > bestScore && isMoveValid(board, moveIterator, color))
    {
      bestMove  = moveIterator;
      bestScore = score;
    }

    moveIterator = moveIterator->nextMove;
  }

  retVal = malloc(sizeof(t_move));
  *retVal = *bestMove;
  //memcpy(retVal, bestMove, sizeof(t_move));

  deleteAllMoves(move);

  return retVal;
}

int     greedyEngine_evaluateBoard(t_board* board, t_color color)
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
        case king:    score += mul*255;
                      break;
      }
    }
  }

  score += rand() % 10;

  return score;
}
