#ifndef _GREEDY_ENGINE
#define _GREEDY_ENGINE

#include "../../move.h"
#include "../../board.h"
#include "../../piece.h"

#include <stdlib.h>
#include <string.h>

t_move* greedyEngine_getMove(t_board* board, t_color color);

int     greedyEngine_evaluateBoard(t_board* board, t_color color);

#endif
