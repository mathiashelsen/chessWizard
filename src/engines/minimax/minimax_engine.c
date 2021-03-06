#include "minimax_engine.h"

t_move* minimaxEngine_getMove(t_board* board, t_color color, int plyDepth)
{
  t_move* move;
  t_move* moveIterator;
  t_move* bestMove;
  t_move* retVal;
  int     bestScore;
  int     score;
  move = getAllMoves(board, color);

  moveIterator  = move;
  bestMove      = NULL;
  bestScore     = INT_MIN;

  /*
   * e.g. black plays, get all moves for black and do the depth search
   */

  while(moveIterator)
  {
    makeMove(board, moveIterator);

    score = minimaxMinAlgo(board, -color, plyDepth-1);

    undoMove(board, moveIterator);

    if(score > bestScore && isMoveValid(board, moveIterator, color))
    {
      bestMove  = moveIterator;
      bestScore = score;
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

int     minimaxMinAlgo(t_board* board, t_color color, int plyDepth)
{
  t_move* allMoves;
  t_move* currentMove;
  int     worstScore;
  int     score;

  // If there is no more depth, evaluate the board
  if(plyDepth == 0)
    return -minimaxEngine_evaluateBoard(board, color);

  worstScore  = INT_MAX;
  score       = 0;
  allMoves    = NULL;
  // Get all your opposites moves
  allMoves    = getAllMoves(board, color);
  currentMove = allMoves;

  while(currentMove)
  {
    makeMove(board, currentMove);

    // For each move, go down recursively, but change sides
    // If the top plyDepth was 2, we are actually calculating
    // the board value for white (-color). Because we are optimizing
    // for black, a positive score from evalBoard is actually a 
    // negative one (hence the minus sign). We still try to find the
    // highest one, because that is the best outcome for black.

    // I.e. the better white does, the worse black does. We want black
    // to win, so white has to have the lowest score. (Or the highest
    // negative one). So: evaluate for white, invert and maximize
    score = minimaxMaxAlgo(board, -color, plyDepth-1); 

    // In the code above, you cant do away with the two minus signs,
    // because we need color to flip between recursive calls.
    if(score < worstScore)
      worstScore = score;

    undoMove(board, currentMove);

    currentMove = currentMove->nextMove;
  }

  deleteAllMoves(allMoves);
  return worstScore;
}

int     minimaxMaxAlgo(t_board* board, t_color color, int plyDepth)
{
  t_move* allMoves;
  t_move* currentMove;
  int     bestScore;
  int     score;

  // If there is no more depth, evaluate the board
  if(plyDepth == 0)
    return minimaxEngine_evaluateBoard(board, color);

  bestScore   = INT_MIN;
  score       = 0;
  allMoves    = NULL;
  // Get all your opposites moves
  allMoves    = getAllMoves(board, color);
  currentMove = allMoves;

  while(currentMove)
  {
    makeMove(board, currentMove);

    // For each move, go down recursively, but change sides
    // If the top plyDepth was 2, we are actually calculating
    // the board value for white (-color). Because we are optimizing
    // for black, a positive score from evalBoard is actually a 
    // negative one (hence the minus sign). We still try to find the
    // highest one, because that is the best outcome for black.

    // I.e. the better white does, the worse black does. We want black
    // to win, so white has to have the lowest score. (Or the highest
    // negative one). So: evaluate for white, invert and maximize
    score = minimaxMinAlgo(board, -color, plyDepth-1); 

    // In the code above, you cant do away with the two minus signs,
    // because we need color to flip between recursive calls.
    if(score > bestScore)
      bestScore = score;

    undoMove(board, currentMove);

    currentMove = currentMove->nextMove;
  }

  deleteAllMoves(allMoves);
  return bestScore;
}


int     minimaxEngine_evaluateBoard(t_board* board, t_color color)
{
  int score;
  score = evaluateBoard(board, color);
  score += rand() % 10;

  return score;
}
