#include "../include/mySimpleComputer.h"
#include "console.h"
#include <stdio.h>

int
main ()
{
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  mt_clrscr ();

  for (int i = 10; i < 20; i++)
    {
      sc_memorySet (i, 2128);
    }

  // Вывод содержимого оперативной памяти
  for (int i = 0; i < MEMORY_SIZE; i++)
    printCell (i, WHITE, BLACK);

  sc_regSet (FLAG_OVERFLOW_MASK, 1);
  sc_regSet (FLAG_DIVISION_BY_ZERO_MASK, 0);
  sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
  sc_regSet (FLAG_INVALID_COMMAND_MASK, 0);
  sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
  printFlags ();
  printDecodedCommand (15);
  printAccumulator ();
  printCounters ();
  mt_gotoXY (18, 0);
  return 0;
}
