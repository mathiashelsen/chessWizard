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

  for(i = 7; i > -1; i--)
  {
    for(j = 0; j < 8; j++)
    {
      if(board->pieces[j + 8*i])
      {
        if((i+j) % 2 == 0)
          printf("\x1B[30;107m%s\x1B[97m\u2590", getPieceShortName(board->pieces[j + 8*i]));
        else
          printf("\x1B[30;100m%s\x1B[90m\u2590", getPieceShortName(board->pieces[j + 8*i]));
      }
      else
      {
        if((i+j) % 2 == 0)
          printf("\x1B[30;107m \x1B[97m\u2590");
        else
          printf("\x1B[30;100m \x1B[90m\u2590");
      }
    }
    printf("\x1B[30;107m%01d\n", i+1);
  }

  printf("A B C D E F G H\n");

  printf("\n\n");
}

void    setupBoard(t_board* board)
{
  t_piece* piece;
  int i;

  // White Pawns
  for(i = 0; i < 8; i++)
  {
      piece         = malloc(sizeof(piece));
      piece->type   = pawn;
      piece->color  = white;
      board->pieces[i + 8] = piece;
  }

  // Black Pawns
  for(i = 0; i < 8; i++)
  {
      piece         = malloc(sizeof(piece));
      piece->type   = pawn;
      piece->color  = black;
      board->pieces[i + 6*8] = piece;
  }

  //White King
  piece             = malloc(sizeof(piece));
  piece->type       = king;
  piece->color      = white;
  board->pieces[4]  = piece;
  //Black King
  piece             = malloc(sizeof(piece));
  piece->type       = king;
  piece->color      = black;
  board->pieces[4+7*8]  = piece;

  //White Queen
  piece             = malloc(sizeof(piece));
  piece->type       = queen;
  piece->color      = white;
  board->pieces[3]  = piece;
  //Black Queen 
  piece             = malloc(sizeof(piece));
  piece->type       = queen;
  piece->color      = black;
  board->pieces[3+7*8]  = piece;

  // Rook
  piece             = malloc(sizeof(piece));
  piece->type       = rook;
  piece->color      = white;
  board->pieces[0+0*8]  = piece;
  piece             = malloc(sizeof(piece));
  piece->type       = rook;
  piece->color      = white;
  board->pieces[7+0*8]  = piece;
  piece             = malloc(sizeof(piece));
  piece->type       = rook;
  piece->color      = black;
  board->pieces[0+7*8]  = piece;
  piece             = malloc(sizeof(piece));
  piece->type       = rook;
  piece->color      = black;
  board->pieces[7+7*8]  = piece;
  
  // Knight
  piece             = malloc(sizeof(piece));
  piece->type       = knight;
  piece->color      = white;
  board->pieces[1+0*8]  = piece;
  piece             = malloc(sizeof(piece));
  piece->type       = knight;
  piece->color      = white;
  board->pieces[6+0*8]  = piece;
  piece             = malloc(sizeof(piece));
  piece->type       = knight;
  piece->color      = black;
  board->pieces[1+7*8]  = piece;
  piece             = malloc(sizeof(piece));
  piece->type       = knight;
  piece->color      = black;
  board->pieces[6+7*8]  = piece;

  // Bishop
  piece             = malloc(sizeof(piece));
  piece->type       = bishop;
  piece->color      = white;
  board->pieces[2+0*8]  = piece;
  piece             = malloc(sizeof(piece));
  piece->type       = bishop;
  piece->color      = white;
  board->pieces[5+0*8]  = piece;
  piece             = malloc(sizeof(piece));
  piece->type       = bishop;
  piece->color      = black;
  board->pieces[2+7*8]  = piece;
  piece             = malloc(sizeof(piece));
  piece->type       = bishop;
  piece->color      = black;
  board->pieces[5+7*8]  = piece;

}
