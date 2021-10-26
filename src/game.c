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
  int     nMoves;

  srand(time(NULL));

  nMoves  = 0;
  player  = white;
  printBoard(game->board);
  while(!isCheckmate(game->board, player) && !isOnlyKings(game->board))
  {
    if(player == black)
    {
      playerMove = randEngine_getMove(game->board, player);
    }
    else
    {
      printBoard(game->board);
      //playerMove = humanPlayer_getMove(game->board, player);
      playerMove  = greedyEngine_getMove(game->board, player);
      nMoves++;
    }

    // We could double check if the move is valid
    // OMITTED
    makeMove(game->board, playerMove);

    playerMove->nextMove  = game->moves;
    game->moves           = playerMove;
   
    player *= -1;
  }

  printf("Player %s has won after %d moves\n", player == white ? "Black" : "White", nMoves);
}
