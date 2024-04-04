#include "console.h"

void
printFlags ()
{
  int flags;

  mt_gotoXY (FLAGS_X, FLAGS_Y);
  if (sc_regGet (0, &flags) == 0)
    {
      printf ("%c   %c   %c   %c   %c\n",
              (flags & FLAG_OVERFLOW_MASK) ? 'O' : '_',
              (flags & FLAG_DIVISION_BY_ZERO_MASK) ? 'Z' : '_',
              (flags & FLAG_OUT_OF_MEMORY_MASK) ? 'M' : '_',
              (flags & FLAG_INVALID_COMMAND_MASK) ? 'E' : '_',
              (flags & FLAG_IGNORE_CLOCK_MASK) ? 'T' : '_');
    }
}
