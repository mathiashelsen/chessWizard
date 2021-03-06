#ifndef _GAME_H
#define _GAME_H

#include "board.h"
#include "move.h"
#include "piece.h"
#include "engines/rand/rand_engine.h"
#include "engines/human/human_player.h"
#include "engines/greedy/greedy_engine.h"
#include "engines/minimax/minimax_engine.h"
#include "engines/alphaBeta/alphaBeta_engine.h"

#include <time.h>
#include <stdlib.h>

typedef struct
{
  t_board*  board;
  t_move*   moves;
} t_game;

t_game*   newGame     (void);
void      endGame     (t_game* game);
void      playGame    (t_game* game);

#endif
