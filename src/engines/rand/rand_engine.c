#include "rand_engine.h"

t_move* rand_engine_getMove(t_board* board, t_color color)
{
  t_move* move;     //Iterator
  t_move* bestMove;
  int     score;
  int     bestScore;

  move      = getAllMoves(board, color);
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

  return bestMove;
  
}
