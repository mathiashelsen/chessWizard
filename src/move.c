#include "move.h"

void    deleteAll(t_move* move)
{
  if(move->nextMove != NULL)
    deleteAll(move->nextMove);

  free(move);
}

t_move* getAllMoves(t_board* board, char pieceIdx)
{
  if(board->pieces[pieceIdx].type == pawn)
  {
    return getAllPawnMoves(board, pieceIdx);
  }
  else
  {
    return NULL;
  }
}

t_move* getAllPawnMoves(t_board* board, char pieceIdx)
{
  printf("Hello world\n");
  return NULL;
}
