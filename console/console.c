#include "console.h"

int
main (int argv, char *argc[])
{
  if (checkConsole (argv, argc))
    return 1;
  mt_clrscr ();

  // Инициализация памяти, регистров и аккумулятора
  sc_memoryInit ();
  sc_regInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();

  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      sc_memorySet (i, rand () % 1000);
    }

  sc_regSet (FLAG_OVERFLOW_MASK, 0);
  sc_regSet (FLAG_DIVISION_BY_ZERO_MASK, 0);
  sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
  sc_regSet (FLAG_INVALID_COMMAND_MASK, 1);
  sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);

  rk_mytermsave ();
  enum keys key;
  while (key != KEY_ESC)
    {
      drawConsole ();
      rk_readkey (&key);
      handleKeypress (&key);
      sleep (0.01);
    }
  return 0;
}