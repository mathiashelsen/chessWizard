#ifndef _MINIMAX_ENGINE
#define _MINIMAX_ENGINE

#include "../../move.h"
#include "../../board.h"
#include "../../piece.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

t_move* minimaxEngine_getMove(t_board* board, t_color color, int plyDepth);

int     minimaxRecAlgo(t_board* board, t_color color, int plyDepth);

int     minimaxEngine_evaluateBoard(t_board* board, t_color color);

#endif
