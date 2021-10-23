#ifndef _BOARD_H
#define _BOARD_H

#include <stdlib.h>

#include "piece.h"

typedef struct
{
  t_piece** pieces;
} t_board;

t_board*  newBoard(void);
void      deleteBoard(t_board* board);
t_piece*  pieceAt(t_board*, char, char);

#endif
