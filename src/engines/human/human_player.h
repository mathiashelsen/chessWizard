#ifndef _HUMAN_PLAYER
#define _HUMAN_PLAYER

#include <stdlib.h>
#include <stdio.h>

#include "../../move.h"
#include "../../board.h"
#include "../../piece.h"

t_move* humanPlayer_getMove(t_board *board, t_color color);

#endif
