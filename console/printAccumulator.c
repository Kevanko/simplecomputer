#include "console.h"

void
printAccumulator ()
{
  int accumulator;
  sc_accumulatorGet (&accumulator);
  mt_gotoXY (0, 127 - 36);
  printf ("sc: +%04x hex: %04X", accumulator, accumulator);
}