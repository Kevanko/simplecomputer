#include <mySimpleComputer.h>

int
sc_regSet (int reg, int value)
{
  if (reg == FLAG_OVERFLOW_MASK || reg == FLAG_ZERO_MASK
      || reg == FLAG_OUT_OF_MEMORY_MASK)
    {
      if (value == 0 || value == 1)
        {
          if (value)
            flags_register |= reg;
          else
            flags_register &= ~reg;
          return 0;
        }
    }
  return -1; // недопустимый регистр или значение
}
