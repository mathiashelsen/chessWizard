#include "testBasics.h"

char runBasicTest(void)
{
  t_board*  board;
  t_piece*  pawn_w0;
  t_piece*  knight_w0;
  t_piece*  king_w;
  t_piece*  pawn_b0;
  t_piece*  rook_w0;
  t_piece*  bishop_b0;
  t_move*   move;

  printf("[Test 1]: Checking checkmate detection\n");

  printf("[Test 1]: Building board\n");
  board     = newBoard();
  pawn_w0   = malloc(sizeof(t_piece));
  pawn_b0   = malloc(sizeof(t_piece));
  king_w    = malloc(sizeof(t_piece));
  knight_w0 = malloc(sizeof(t_piece));
  rook_w0   = malloc(sizeof(t_piece));
  bishop_b0 = malloc(sizeof(t_piece));

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

  rook_w0->type   = rook;
  rook_w0->color  = white;
  board->pieces[2 + 5*8] = rook_w0;

  bishop_b0->type = bishop;
  bishop_b0->color  = black;
  board->pieces[3 + 6*8] = bishop_b0;

  printf("[Test 1]: Board finished:\n");
  printBoard(board);

  printf("[Test 1]: Moves for white are:\n");
  move = getAllMoves(board, white);
  if(move)
    printAllMoves(board, move);
  else
    printf("No valid moves were found\n");

  printf("[Test 1]: Moves for black are:\n");
  move = getAllMoves(board, black);
  if(move)
    printAllMoves(board, move);
  else
    printf("No valid moves were found\n");

  move = sortMoves(move);
  printf("[Test 1]: Sorted moves for black are:\n");
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

char runCheckmateTest(void)
{
  t_board*  board;
  t_piece*  pawn_w0;
  t_piece*  pawn_w1;
  t_piece*  king_w;

  t_piece*  rook_b0;
  t_piece*  bishop_b0;

  printf("[Test 1]: Checking checkmate detection\n");

  printf("[Test 1]: Building board\n");
  board     = newBoard();
  pawn_w0   = malloc(sizeof(t_piece));
  pawn_w1   = malloc(sizeof(t_piece));
  king_w    = malloc(sizeof(t_piece));

  rook_b0   = malloc(sizeof(t_piece));
  bishop_b0 = malloc(sizeof(t_piece));

  pawn_w0->type   = pawn;
  pawn_w0->color  = white;
  board->pieces[0 + 1*8] = pawn_w0;

  pawn_w1->type   = pawn;
  pawn_w1->color  = white;
  board->pieces[1 + 1*8] = pawn_w1;

  king_w->type    = king;
  king_w->color   = white;
  board->pieces[1 + 0*8] = king_w;

  rook_b0->type   = rook;
  rook_b0->color  = black;
  board->pieces[5 + 0*8] = rook_b0;

  bishop_b0->type = bishop;
  bishop_b0->color  = black;
  board->pieces[5 + 4*8] = bishop_b0;

  printBoard(board);
  printf("[Test 1]: Is white checkmate?...%c\n", isCheckmate(board, white) ? 'y' : 'n');

  board->pieces[1 + 1*8] = NULL;
  board->pieces[1 + 2*8] = pawn_w1;

  printBoard(board);
  printf("[Test 1]: Is white checkmate?...%c\n", isCheckmate(board, white) ? 'y' : 'n');


  deleteBoard(board);

  return 0;
}

char runCheckmateTest_2(void)
{
  t_board*  board;
  t_move*   move;

  t_piece*  king_w;
  t_piece*  queen_b;
  t_piece*  knight_b;

  printf("[Test 1]: Checking checkmate detection\n");

  printf("[Test 1]: Building board\n");
  board     = newBoard();
  king_w    = malloc(sizeof(t_piece));
  queen_b   = malloc(sizeof(t_piece));
  knight_b  = malloc(sizeof(t_piece));


  king_w->type            = king;
  king_w->color           = white;
  board->pieces[0 + 0*8]  = king_w;

  queen_b->type           = queen;
  queen_b->color          = black;
  board->pieces[1 + 1*8]  = queen_b;

  knight_b->type          = knight;
  knight_b->color         = black;
  board->pieces[3 + 0*8]  = knight_b;

  printBoard(board);
  printf("[Test 1]: Is white checkmate?...%c\n", isCheckmate(board, white) ? 'y' : 'n');

  printf("[Test 1]: Moves for white are:\n");
  move = getAllMoves(board, white);
  if(move)
    printAllMoves(board, move);
  else
    printf("No valid moves were found\n");

  printf("[Test 1]: Moves for black are:\n");
  move = getAllMoves(board, black);
  if(move)
    printAllMoves(board, move);
  else
    printf("No valid moves were found\n");

  deleteBoard(board);

  return 0;
}
