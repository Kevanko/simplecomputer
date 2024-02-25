#include <mySimpleComputer.h>

int
sc_accumulatorGet (int *value)
{
  if (!value)
    return -1; // неверный указатель
  *value = accumulator;
  return 0;
}