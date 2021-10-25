#ifndef _RAND_ENGINE_H
#define _RAND_ENGINE_H

#include "../../move.h"
#include "../../board.h"
#include "../../piece.h"

#include <stdlib.h>

t_move* rand_engine_getMove(t_board* board, t_color color);

#endif
