#include "console.h"

void
printDecodedCommand (int value)
{
  mt_gotoXY (COMMAND_X, COMMAND_Y);
  printf ("dec: %d", value);
  printf ("| oct: %o", value);
  printf ("| hex: %X", value);
  printf ("       bin: ");
  for (int i = 14; i >= 0; i--)
    {
      printf ("%d", (value >> i) & 1);
    }
}