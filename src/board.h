#ifndef _BOARD_H
#define _BOARD_H

#include <stdlib.h>
#include <stdio.h>

#include "piece.h"

typedef struct
{
  t_piece** pieces;
} t_board;

t_board*  newBoard      (void);
void      deleteBoard   (t_board* board);
t_piece*  pieceAt       (t_board*, char, char);

int       isOnlyKings   (t_board* board);
int       evaluateBoard (t_board* board, t_color color);

void      printBoard    (t_board* board);
void      setupBoard    (t_board* board);

#endif
