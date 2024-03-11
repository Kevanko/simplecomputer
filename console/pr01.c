#include "console.h"

// Приложение console
int
main ()
{
  if (!isatty (STDOUT_FILENO))
    {
      printf ("Error: Output is not a terminal\n");
      return 1;
    }

  int rows, cols;
  mt_getscreensize (&rows, &cols);
  if (rows < INOUT_BLOCK_HEIGHT + INOUT_BLOCK_Y + 1 || cols < FLAGS_X + 9)
    {
      printf ("Error: Terminal window is too small\n");
      return 1;
    }

  mt_clrscr ();

  // Инициализация памяти, регистров и аккумулятора
  sc_memoryInit ();
  sc_regInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();

  sc_regSet (FLAG_OVERFLOW_MASK, 0);
  sc_regSet (FLAG_DIVISION_BY_ZERO_MASK, 0);
  sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
  sc_regSet (FLAG_INVALID_COMMAND_MASK, 1);
  sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);

  // Вывод текстовых данных консоли
  printMemory ();
  printFlags ();
  printDecodedCommand (15);
  printAccumulator ();
  printCounters ();
  printCommand ();

  // Вывод 7 произвольных ячеек в блок IN-OUT
  for (int i = 0; i < 7; i++)
    {
      printTerm (i, 1);
    }

  mt_gotoXY (0, 25);
  return 0;
}