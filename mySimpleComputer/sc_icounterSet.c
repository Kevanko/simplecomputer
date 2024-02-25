#include <mySimpleComputer.h>

int
sc_icounterSet (int value)
{
  if (value < 0 || value > USHRT_MAX)
    {
      return -1; // Недопустимое значение
    }
  instruction_counter = value;
  return 0;
}