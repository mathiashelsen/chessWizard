#include "rand_engine.h"

t_move* randEngine_getMove(t_board* board, t_color color)
{
  t_move* move;     //Iterator
  t_move* bestMove;
  t_move* retVal;
  t_move* LL_root;
  int     score;
  int     bestScore;

  move      = getAllMoves(board, color);
  LL_root   = move;
  //printf("Playing with %s\n", color > 0 ? "White" : "Black");
  //printAllMoves(board, move);
  bestScore = -1;

  while(move)
  {
      score = rand() % 1024;
      if(  score > bestScore
        && isMoveValid(board, move, color))
      {
        bestScore = score;
        bestMove  = move;
      }

      move = move->nextMove;
  }

  retVal  = malloc(sizeof(t_move));
  memcpy(retVal, bestMove, sizeof(t_move));
  //*retVal = *bestMove;

  deleteAllMoves(LL_root);

  return retVal;
  
}
