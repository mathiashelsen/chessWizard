#ifndef _PIECE_H
#define _PIECE_H

typedef enum
{
  pawn,
  rook,
  bishop,
  queen,
  king
} t_pieceType;

typedef enum
{
  active,
  idle
} t_pieceStatus;

typedef struct
{
  t_pieceStatus status;
  t_pieceType   type;
  char  x;
  char  y;
} t_piece;

#endif
