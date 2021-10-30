#ifndef _ALPHABETA_ENGINE
#define _ALPHABETA_ENGINE

#include "../../move.h"
#include "../../board.h"
#include "../../piece.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

t_move* alphaBetaEngine_getMove(t_board* board, t_color color, int plyDepth);

int     alphaBetaMaxAlgo(t_board* board, t_color color, int plyDepth, int alpha, int beta);
int     alphaBetaMinAlgo(t_board* board, t_color color, int plyDepth, int alpha, int beta);

int     alphaBetaEngine_evaluateBoard(t_board* board, t_color color);

#endif
