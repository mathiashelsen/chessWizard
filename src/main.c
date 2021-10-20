#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "piece.h"
#include "move.h"

int main(void)
{
  t_board* myBoard = newBoard();

  printf("Allocated board at: %p\n", myBoard);

  deleteBoard(myBoard);

  t_move myMove_A = {.x = 2, .y = -1, .nextMove = NULL};
  t_move myMove_B = {.x = 0, .y = 2,  .nextMove = &myMove_A};

  return EXIT_SUCCESS;
}
