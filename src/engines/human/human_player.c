#include "human_player.h"

t_move* humanPlayer_getMove(t_board* board, t_color color)
{
  t_move* move;
  int nTokens;
  char x_1, x_2;
  int from_x, from_y, to_x, to_y;
  nTokens = 0;
  move    = NULL;

  while(!move)
  {
    while(nTokens != 4)
    {
      printf("> Please enter move: ");
      nTokens = scanf("%c%d %c%d", &x_1, &from_y, &x_2, &to_y);
    }

    from_x = x_1 - 'a';
    from_y--;
    to_x   = x_2 - 'a';
    to_y--;

    move  = malloc(sizeof(move));
    move->from_x  = from_x;
    move->from_y  = from_y;
    move->to_x    = to_x;
    move->to_y    = to_y;
    move->capturedPiece = board->pieces[to_x + 8*to_y];

    if(   !board->pieces[from_x + 8*from_y]
      ||  board->pieces[from_x + 8*from_y]->color != color
      ||  !isMovePseudoValid(board, to_x, to_y, color)
      ||  !isMoveValid(board, move, color))
    {
      free(move);
      move = NULL;
    }
  }

  return move;
}
