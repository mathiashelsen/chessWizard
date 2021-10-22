#include "board.h"

t_board*  newBoard(void)
{
  int i;
  t_board* board  = malloc(sizeof(t_board));
  board->pieces   = malloc(64*sizeof(t_piece *)); 
  for(i = 0; i < 64; i++)
  {
      board->pieces[i] = NULL;
  }

  return board;
}

void      deleteBoard(t_board* board)
{
  int i;
  for(i = 0; i <64; i++)
  {
    if(board->pieces[i])
      free(board->pieces[i]);
  }
  free(board->pieces);
  free(board);
}

t_piece*  pieceAt(t_board* board, char x, char y)
{
  if(x > -1 && x < 8 && y > -1 && y < 8)
  {
    return board->pieces[x + y*8];
  }
  else
  {
    return NULL;
  }
}
