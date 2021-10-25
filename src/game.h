#ifndef _GAME_H
#define _GAME_H

#include "board.h"
#include "move.h"
#include "piece.h"

typedef struct
{
  t_board*  board;
  t_move*   moves;
} t_game;

t_game*   newGame(void);
void      endGame(t_game* game);

#endif
