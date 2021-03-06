#ifndef _RAND_ENGINE_H
#define _RAND_ENGINE_H

#include "../../move.h"
#include "../../board.h"
#include "../../piece.h"

#include <stdlib.h>
#include <string.h>

t_move* randEngine_getMove(t_board* board, t_color color);
int     greedyEngine_evaluateBoard(t_board* board, t_color color);

#endif
