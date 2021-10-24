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

const char* getPieceShortName(t_piece *piece)
{
  if(piece->color == white)
  {
    switch(piece->type)
    {
      case pawn:    return "Pw";
      case rook:    return "Rw";
      case bishop:  return "Bw";
      case knight:  return "Nw";
      case queen:   return "Qw";
      case king:    return "Kw";
      default:      return "Huh?";
    }
  }else{
    switch(piece->type)
    {
      case pawn:    return "Pb";
      case rook:    return "Rb";
      case bishop:  return "Bb";
      case knight:  return "Nb";
      case queen:   return "Qb";
      case king:    return "Kb";
      default:      return "Huh?";
    }

  }
}

