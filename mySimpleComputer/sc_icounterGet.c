#include <mySimpleComputer.h>

int
sc_icounterGet (int *value)
{
  if (!value)
    return -1; // неверный указатель
  *value = instruction_counter;
  return 0;
}