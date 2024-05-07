#include "console.h"

void
printAccumulator ()
{
  int accum, invert_accum;
  sc_accumulatorGet (&accum);
  mt_gotoXY (ACCUMULATOR_X, ACCUMULATOR_Y);
  if ((accum >> 14) & 1)
    {
      printf ("sc: -");
      invert_accum = (~accum + 1) & 0x7FFF;
    }
  else
    {
      printf ("sc: +");
      invert_accum = accum;
    }
  printf ("%04x hex: %04X", invert_accum, accum);
}