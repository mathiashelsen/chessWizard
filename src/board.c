#include "board.h"

t_board*  newBoard(void)
{
  t_board* board  = malloc(sizeof(t_board));
  board->pieces   = malloc(64*sizeof(t_piece)); 
  return board;
}

void      deleteBoard(t_board* board)
{
  free(board->pieces);
  free(board);
}

t_piece*  pieceAt(t_board* board, char x, char y)
{
  return &(board->pieces[x + y*8]);
}
