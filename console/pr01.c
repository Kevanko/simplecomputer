#include "console.h"

int
main (int argv, char *argc[])
{
  generateFont ();
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

  // Открываем файл для чтения
  FILE *file = fopen (argv > 1 ? argc[1] : "font.bin", "rb");
  if (file == NULL)
    {
      printf ("Ошибка шрифт не найден\n");
      return 1;
    }
  int read_result;
  bc_bigcharread (fileno (file), (int *)font, FONT_SIZE, &read_result);
  fclose (file);
  if (read_result == FONT_SIZE - 1)
    {
      printf ("Ошибка при чтении шрифта из файла\n");
      return 1;
    }

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

  // Вывод текстовых данных консоли
  bc_box (1, 1, 63, 15, WHITE, BLACK, "Оперативная память", RED, BLACK);
  printMemory ();
  bc_box (1, 16, 63, 18, WHITE, BLACK, "Редактируемая ячейка (Формат)", RED,
          BLACK);
  printDecodedCommand (memory[ACTIVE_MEMORY]);
  bc_box (64, 1, 86, 3, WHITE, BLACK, "Аккумулятор", RED, BLACK);
  printAccumulator ();
  bc_box (64, 4, 86, 6, WHITE, BLACK, "Счетчик команд", RED, BLACK);
  printCounters ();
  bc_box (87, 1, 114, 3, WHITE, BLACK, "Регистр флагов", RED, BLACK);
  printFlags ();
  bc_box (87, 4, 114, 6, WHITE, BLACK, "Команда", RED, BLACK);
  printCommand ();

  for (int i = 0; i < 8; i++)
    {
      printTerm (i, 1);
    }
  bc_box (67, 19, 80, 24, WHITE, BLACK, "IN--OUT", GREEN, BLACK);

  bc_box (64, 7, 114, 18, WHITE, BLACK, "Редактируемая ячейка (увеличино)",
          RED, BLACK);

  printBigCell (memory[ACTIVE_MEMORY], 67, 9);
  mt_gotoXY (0, 25);
  return 0;
}