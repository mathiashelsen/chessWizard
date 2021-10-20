#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "piece.h"

int main(void)
{
  t_board* myBoard = newBoard();

  printf("Allocated board at: %p\n", myBoard);

  deleteBoard(myBoard);

  return EXIT_SUCCESS;
}
