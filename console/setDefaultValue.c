#include "console.h"

int
setDefaultValue ()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    sc_memorySet (i, 0);

  sc_accumulatorSet (0);
  sc_icounterSet (0);
  sc_regSet (FLAG_OVERFLOW_MASK, 0);
  sc_regSet (FLAG_DIVISION_BY_ZERO_MASK, 0);
  sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
  sc_regSet (FLAG_INVALID_COMMAND_MASK, 1);
  sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);

  return 0;
}