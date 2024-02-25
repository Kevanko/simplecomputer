#include <mySimpleComputer.h>

int
sc_regGet (int reg, int *value)
{
  if (!value)
    return -1; // неверный указатель
  if (reg == FLAG_OVERFLOW_MASK || reg == FLAG_ZERO_MASK
      || reg == FLAG_OUT_OF_MEMORY_MASK)
    {
      *value = (flags_register & reg) ? 1 : 0;
      return 0;
    }
  else if (reg == 0) // Если reg равен 0, запросить все флаги
    {
      *value = flags_register;
      return 0;
    }
  return -1; // недопустимый регистр
}
