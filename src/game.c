#include "game.h"

t_game*   newGame(void)
{
  t_game* game;
  game        = malloc(sizeof(game));
  game->board = newBoard();
  game->moves = NULL;

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
