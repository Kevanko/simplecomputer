#include "console.h"

void
printAccumulator ()
{
  int accumulator;
  sc_accumulatorGet (&accumulator);
  mt_gotoXY (ACCUMULATOR_X, ACCUMULATOR_Y);
  printf ("sc: +%04x hex: %04X", accumulator, accumulator);
}