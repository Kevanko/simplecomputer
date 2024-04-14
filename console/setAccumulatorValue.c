#include "console.h"

int
setAccumulatorValue ()
{
  mt_gotoXY (ACCUMULATOR_X + 4, ACCUMULATOR_Y);
  int number;
  rk_readvalue (&number, 0);
  sc_accumulatorSet (number);
  return 0;
}