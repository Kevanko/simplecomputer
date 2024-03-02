#include <mySimpleComputer.h>

int
sc_accumulatorSet (int value)
{
  if (value < 0 || value > 0x7FFF)
    {
      return -1; // Недопустимое значение
    }
  accumulator = value;
  return 0;
}