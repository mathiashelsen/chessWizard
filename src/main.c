#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "piece.h"
#include "move.h"

int main(void)
{
  t_board* myBoard = newBoard();

  printf("Allocated board at: %p\n", myBoard);

  t_piece* myPawn = malloc(sizeof(t_piece));
  t_piece* computerPawn = malloc(sizeof(t_piece));
  myPawn->type  = pawn; 
  myPawn->color = white;
  computerPawn->type  = pawn; 
  computerPawn->color = black;
  myBoard->pieces[3 + 1*8] = myPawn;
  myBoard->pieces[4 + 2*8] = computerPawn;

  t_move* allMoves = getAllMoves(myBoard, white);

  if(allMoves)
    printAllMoves(myBoard, allMoves);
  else
    printf("No valid moves were found");

  printf("Is the first move valid?: %01d\n", isMoveValid(myBoard, allMoves, white));
  printBoard(myBoard);
  makeMove(myBoard, allMoves);
  printBoard(myBoard);
  undoMove(myBoard, allMoves);
  printBoard(myBoard);

  deleteAllMoves(allMoves);
  deleteBoard(myBoard);

  return EXIT_SUCCESS;
}
