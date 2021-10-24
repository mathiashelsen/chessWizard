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
      case pawn:    return "\u2659";
      case rook:    return "\u2656";
      case bishop:  return "\u2657";
      case knight:  return "\u2658";
      case queen:   return "\u2655";
      case king:    return "\u2654";
      default:      return "Huh?";
    }
  }else{
    switch(piece->type)
    {
      case pawn:    return "\u265f";
      case rook:    return "\u265c";
      case bishop:  return "\u265d";
      case knight:  return "\u265e";
      case queen:   return "\u265b";
      case king:    return "\u265a";
      default:      return "Huh?";
    }

  }
}

