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

void    printBoard(t_board* board)
{
  int i, j;
  printf("\n\n");

  printf("\n-------------------------\n");
  for(i = 7; i > -1; i--)
  {
    for(j = 0; j < 8; j++)
    {
      if(board->pieces[j + 8*i])
        printf("|%s", getPieceShortName(board->pieces[j + 8*i]));
      else
        printf("|  ");
    }
    printf("|  %01d\n-------------------------\n", i+1);
  }

  printf("  A  B  C  D  E  F  G  H\n");

  printf("\n\n");
}
