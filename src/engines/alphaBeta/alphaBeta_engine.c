#include "alphaBeta_engine.h"

t_move* alphaBetaEngine_getMove(t_board* board, t_color color, int plyDepth)
{
  t_move* move;
  t_move* moveIterator;
  t_move* bestMove;
  t_move* retVal;
  int     score;
  int     alpha;
  int     beta;
  move = getAllMoves(board, color);

  moveIterator  = move;
  bestMove      = NULL;
  alpha         = INT_MIN;
  beta          = INT_MAX;

  /*
   * e.g. black plays, get all moves for black and do the depth search
   */

  while(moveIterator)
  {
    makeMove(board, moveIterator);

    score = alphaBetaRecAlgo(board, color, plyDepth-1, alpha, beta);

    undoMove(board, moveIterator);

    if(score > alpha && isMoveValid(board, moveIterator, color))
    {
      bestMove  = moveIterator;
      alpha     = score;
    }

    moveIterator = moveIterator->nextMove;
  }
  
  if(!bestMove)
  {
    printf("ERROR: Could not determine bestMove\n");
  }
  retVal  = malloc(sizeof(t_move));
  memcpy(retVal, bestMove, sizeof(t_move));

  deleteAllMoves(move);

  return retVal;
}

int     alphaBetaRecAlgo(t_board* board, t_color color, int plyDepth, int alpha, int beta)
{
  t_move* allMoves;
  t_move* currentMove;
  int     score;

  // If there is no more depth, evaluate the board
  if(plyDepth == 0)
    return alphaBetaEngine_evaluateBoard(board, color);

  score       = 0;
  allMoves    = NULL;
  // Get all your opposites moves
  allMoves    = getAllMoves(board, -color);
  currentMove = allMoves;

  while(currentMove)
  {
    makeMove(board, currentMove);

    score = -alphaBetaRecAlgo(board, -color, plyDepth-1, -beta, -alpha); 

    undoMove(board, currentMove);

    if(score > alpha )
      alpha = score;

    if(score >= beta )
    {
      deleteAllMoves(allMoves);
      return beta;
    }

    currentMove = currentMove->nextMove;
  }

  deleteAllMoves(allMoves);
  return alpha;
}

int     alphaBetaEngine_evaluateBoard(t_board* board, t_color color)
{
  int i;
  int score;
  int mul;


  score = 0;
  mul   = 1;

  for(i = 0; i < 64; i++)
  {
    if( board->pieces[i] )
    {
      if(board->pieces[i]->color == color)
        mul = 10;
      else
        mul = -10;

      switch(board->pieces[i]->type)
      {
        case pawn:    score += mul*1;
                      break;
        case knight:  score += mul*3;
                      break;
        case bishop:  score += mul*3;
                      break;
        case rook:    score += mul*5;
                      break;
        case queen:   score += mul*9;
                      break;
        case king:    score += mul*2;
                      break;
      }
    }
  }

  score += rand() % 10;

  return score;
}
