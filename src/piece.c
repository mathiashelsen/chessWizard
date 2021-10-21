#include "piece.h"

const char* getPieceName(t_piece *piece)
{
  switch(piece->type)
  {
    case pawn:    return "Pawn";
    case rook:    return "Rook";
    case bishop:  return "Bishop";
    case knight:  return "Knight";
    case queen:   return "Queen";
    case king:    return "King";
    default:      return "Huh?";
  }
}

