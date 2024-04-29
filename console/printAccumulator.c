#include "console.h"

void
printAccumulator ()
{
  int accum;
  sc_accumulatorGet (&accum);
  mt_gotoXY (ACCUMULATOR_X, ACCUMULATOR_Y);
  printf ("sc: +%04x hex: %04X", accum, accum);
}