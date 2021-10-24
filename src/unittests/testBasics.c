#include "testBasics.h"

char runBasicTest(void)
{
  t_board*  board;
  t_piece*  pawn_w0;
  t_piece*  knight_w0;
  t_piece*  king_w;
  t_piece*  pawn_b0;
  t_move*   move;

  printf("[Test 1]: Checking checkmate detection\n");

  printf("[Test 1]: Building board\n");
  board     = newBoard();
  pawn_w0   = malloc(sizeof(t_piece));
  pawn_b0   = malloc(sizeof(t_piece));
  king_w    = malloc(sizeof(t_piece));
  knight_w0 = malloc(sizeof(t_piece));

  pawn_w0->type   = pawn;
  pawn_w0->color  = white;
  board->pieces[2 + 1*8] = pawn_w0;

  king_w->type    = king;
  king_w->color   = white;
  board->pieces[3 + 1*8] = king_w;

  pawn_b0->type   = pawn;
  pawn_b0->color  = black;
  board->pieces[4 + 2*8] = pawn_b0;

  knight_w0->type = knight;
  knight_w0->color = white;
  board->pieces[0] = knight_w0;

  printf("[Test 1]: Board finished:\n");
  printBoard(board);

  printf("[Test 1]: Moves for white are:\n");
  move = getAllMoves(board, white);
  if(move)
    printAllMoves(board, move);
  else
    printf("No valid moves were found\n");

  printf("[Test 1]: Is white checkmate?...%c\n", isCheckmate(board, white) ? 'y' : 'n');

  printf("[Test 1]: Cleaning up\n");
  deleteAllMoves(move);

  printf("[Test 1]: Moving pawn\n");
  board->pieces[2 + 1*8] = NULL;
  board->pieces[5 + 1*8] = pawn_w0;
  printBoard(board);

  printf("[Test 1]: Is white checkmate?...%c\n", isCheckmate(board, white) ? 'y' : 'n');
  deleteBoard(board);

  return 0;
}
