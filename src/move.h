#ifndef _MOVE_H
#define _MOVE_H

#include "piece.h"
#include "board.h"

#include <stdio.h>

typedef enum
{
  quiet, 
  capture,
  promotion 
} t_moveType;

typedef struct t_move
{
  char            from_x;
  char            from_y;
  char            to_x;
  char            to_y;
  t_moveType      moveType;
  t_piece*        capturedPiece;
  struct t_move*  nextMove;
} t_move;

void    deleteAllMoves(t_move* move);

void    printAllMoves(t_board* board, t_move* move);

t_move* getLastMove(t_move* move);

void    concatenateMovesList(t_move* listA, t_move* listB);

t_move* getAllMoves(t_board* board, t_color color);

t_move* getAllPawnMoves   (t_board* board, char pieceIdx);
t_move* getAllKingMoves   (t_board* board, char pieceIdx);
t_move* getAllKnightMoves (t_board* board, char pieceIdx);
t_move* getAllRookMoves   (t_board* board, char pieceIdx);
t_move* getAllBishopMoves (t_board* board, char pieceIdx);

t_move* getLinearStepMoves(t_board* board, char pieceIdx, char x_step, char y_step);

void    makeMove          (t_board* board, t_move* move);
void    undoMove          (t_board* board, t_move* move);
char    isMovePseudoValid (t_board* board, char x, char y, t_color color);
char    isMoveValid       (t_board* board, t_move* move, t_color color);
char    isKingUnderAttack (t_board* board, t_color color);
char    isCheckmate       (t_board* board, t_color color);

#endif
