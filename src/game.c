#include "game.h"

t_game*   newGame(void)
{
  t_game* game;
  game        = malloc(sizeof(game));
  game->board = newBoard();
  game->moves = NULL;

  setupBoard(game->board);

  return game;
}

void      endGame(t_game* game)
{
  t_move* move;

  // Delete the board and all the pieces on it
  deleteBoard(game->board);

  // Delete all the captured pieces
  move = game->moves;
  while(move)
  {
    if(move->capturedPiece)
      free(move->capturedPiece);

    move = move->nextMove;
  }

  // Delete all the moves
  deleteAllMoves(game->moves);

  // Delete the game 
  free(game);
}

void      playGame(t_game* game)
{
  t_color player;
  t_move* playerMove;

  player = white;
  printBoard(game->board);
  while(!isCheckmate(game->board, player))
  {
    playerMove = rand_engine_getMove(game->board, player);

    // We could double check if the move is valid
    // OMITTED
    makeMove(game->board, playerMove);

    playerMove->nextMove  = game->moves;
    game->moves           = playerMove;
   
    printBoard(game->board);
    printf("--- Please press any key to continue ---\n");
    getchar();

    player *= -1;
  }
}
