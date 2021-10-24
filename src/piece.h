#ifndef _PIECE_H
#define _PIECE_H

typedef enum
{
  pawn,
  rook,
  bishop,
  knight,
  queen,
  king
} t_pieceType;

typedef enum
{
  active,
  idle
} t_pieceStatus;

typedef enum
{
  white = 1,
  black = -1
} t_color;

typedef struct
{
  // Hmmm, this is not required because idle pieces will not be present on the board
  // t_pieceStatus status;
  t_pieceType   type;
  // White = 1 (moves up), black = -1 (moves down)
  t_color       color;
} t_piece;

const char* getPieceName      (t_piece* piece);
const char* getPieceShortName (t_piece* piece);

#endif
