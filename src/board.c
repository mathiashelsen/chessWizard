#include "board.h"

t_board*  newBoard(void)
{
  t_board* board  = malloc(sizeof(t_board));
  board->pieces   = malloc(32*sizeof(t_piece)); 
  return board;
}

void      deleteBoard(t_board* board)
{
  free(board->pieces);
  free(board);
}
