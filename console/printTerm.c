#include "console.h"

void
printTerm (int address, int input)
{
  static int line = 0;
  mt_gotoXY (INOUT_BLOCK_X, INOUT_BLOCK_Y + line);
  if (input)
    {
      printf ("%03d> +%04X", address, memory[address]);
    }
  else
    {
      printf ("%03d<         ", address);
    }
  line = (line + 1) % INOUT_BLOCK_HEIGHT;
}