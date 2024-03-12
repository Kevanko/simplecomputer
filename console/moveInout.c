#include "console.h"

void
moveInout ()
{
  for (int i = INOUT_BLOCK_HEIGHT - 1; i > 0; i--)
    {
      INOUT_ARRAY[i] = INOUT_ARRAY[i - 1];
      INOUT_INPUT[i] = INOUT_INPUT[i - 1];
    }
}