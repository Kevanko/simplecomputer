#include <mySimpleComputer.h>

extern int accumulator;
extern int instruction_counter;
extern int flags_register;

// Функции инициализации
int
sc_regInit (void)
{
  flags_register = DEFAULT_FLAGS_VALUE;
  return 0;
}

int
sc_accumulatorInit (void)
{
  accumulator = DEFAULT_ACCUMULATOR_VALUE;
  return 0;
}

int
sc_icounterInit (void)
{
  instruction_counter = DEFAULT_COUNTER_VALUE;
  return 0;
}

// Функции установки значений
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

int
sc_accumulatorSet (int value)
{
  accumulator = value;
  return 0;
}

int
sc_icounterSet (int value)
{
  instruction_counter = value;
  return 0;
}

// Функции получения значений
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

int
sc_accumulatorGet (int *value)
{
  if (!value)
    return -1; // неверный указатель
  *value = accumulator;
  return 0;
}

int
sc_icounterGet (int *value)
{
  if (!value)
    return -1; // неверный указатель
  *value = instruction_counter;
  return 0;
}