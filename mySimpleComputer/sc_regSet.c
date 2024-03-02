#include <mySimpleComputer.h>

int
sc_regSet (int reg, int value)
{
  if (reg < 0 || reg > 5)
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
