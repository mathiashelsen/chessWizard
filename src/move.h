#ifndef _MOVE_H
#define _MOVE_H

#include "piece.h"
#include "board.h"

#include <stdio.h>

typedef struct t_move
{
  char            from_x;
  char            from_y;
  char            to_x;
  char            to_y;
  struct t_move*  nextMove;
} t_move;

void    deleteAllMoves(t_move* move);

void    printAllMoves(t_move* move);

t_move* getLastMove(t_move* move);

void    concatenateMovesList(t_move* listA, t_move* listB);

t_move* getAllMoves(t_board* board, t_color color);

t_move* getAllPawnMoves(t_board* board, char pieceIdx);

#endif
