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
  bestScore     = -10000;

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
  
  if(!bestMove)
  {
    printf("ERROR: Could not determine bestMove\n");
  }
  retVal  = malloc(sizeof(t_move));
  memcpy(retVal, bestMove, sizeof(t_move));

  deleteAllMoves(move);

  return retVal;
}

int     greedyEngine_evaluateBoard(t_board* board, t_color color)
{
  int score;
  score = evaluateBoard(board, color);
  score += rand() % 10;

  return score;
}
