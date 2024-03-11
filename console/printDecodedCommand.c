#include "console.h"

void
printDecodedCommand (int value)
{
  mt_gotoXY (DECODE_X, DECODE_Y);
  printf ("dec: %05d", value);
  printf ("| oct: %05o", value);
  printf ("| hex: %04X", value);
  printf ("      bin: ");
  for (int i = 14; i >= 0; i--)
    {
      printf ("%d", (value >> i) & 1);
    }
}