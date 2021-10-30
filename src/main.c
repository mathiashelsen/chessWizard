#include <stdio.h>
#include <stdlib.h>

//#include "board.h"
//#include "piece.h"
//#include "move.h"
//#include "unittests/testBasics.h"
#include "game.h"

int main(void)
{
  t_game* game;
  int i;

  srand(time(NULL));
  for(i = 0; i < 10; i++)
  {
    game = newGame();
    playGame(game);
    endGame(game);
  }
  //char retVal;

  //retVal = runBasicTest();
  //retVal = runCheckmateTest();
  //retVal = runCheckmateTest_2();

  return EXIT_SUCCESS;
}
