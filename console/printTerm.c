#include "console.h"

void
printTerm (int address, int input)
{
  if (address >= 0)
    {
      moveInout ();
      INOUT_ARRAY[0] = address;
      INOUT_INPUT[0] = input;
    }
  for (int i = 0; i < INOUT_BLOCK_HEIGHT; i++)
    {
      mt_gotoXY (INOUT_BLOCK_X, INOUT_BLOCK_Y + i);
      if (INOUT_INPUT[i] == -1)
        {
          if ((INOUT_ARRAY[i] >> 14) & 1)
            printf ("%03d> -%04X", INOUT_ARRAY[i], memory[INOUT_ARRAY[i]]);
          else
            printf ("%03d> +%04X", INOUT_ARRAY[i], memory[INOUT_ARRAY[i]]);
        }
      else
        {
          if ((INOUT_ARRAY[i] >> 14) & 1)
            printf ("%03d< -%04X", INOUT_ARRAY[i], INOUT_INPUT[i]);
          else
            printf ("%03d< +%04X", INOUT_ARRAY[i], INOUT_INPUT[i]);
        }
      mt_gotoXY (0, 30);
    }
}