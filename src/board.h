#ifndef _BOARD_H
#define _BOARD_H

#include <stdlib.h>

#include "piece.h"

typedef struct
{
  t_piece*  pieces;
} t_board;

typedef enum
{
  black,
  white
} t_color;

t_board*  newBoard(void);
void      deleteBoard(t_board* board);

#endif
