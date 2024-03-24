#include "console.h"

// Пример значений для символов '0' - '9'
int font[17][2] = {
  { 0x818181FF, 0xFF818181 }, // 0
  { 0x2424243C, 0x24242424 }, // 1
  { 0xE1A5A59A, 0x8F8985A5 }, // 2
  { 0x1818187E, 0x18181818 }, // 3
  { 0x464E5A71, 0x00000000 }, // 4
  { 0x81818181, 0x81818181 }, // 5
  { 0xC183858D, 0x91A1C0C0 }, // 6
  { 0x0103060E, 0x10101010 }, // 7
  { 0x8D929294, 0x82848C90 }, // 8
  { 0x4646463C, 0x46464646 }, // 9
  { 0x4646463C, 0x46464646 }, // a
  { 0x4646463C, 0x46464646 }, // b
  { 0x4646463C, 0x46464646 }, // c
  { 0x4646463C, 0x46464646 }, // d
  { 0x4646463C, 0x46464646 }, // e
  { 0x00111111, 0x46464646 }, // f
  { 0xFF181800, 0x001818FF }  // +
};

// Функция для преобразования числа в символ Х16
void
printBigCell2 (char cell[4], int x, int y)
{
  int numbers[4];
  for (int i = 0; i < 4; ++i)
    {
      numbers[i] = cell[i] - '0';
    }

  bc_printbigchar (font[16], x, y, 0, 0);

  for (int i = 0; i < 4; ++i)
    {
      if (numbers[i] >= 0 && numbers[i] <= 15)
        {
          bc_printbigchar (font[numbers[i]], x + (i + 1) * 9, y, 0, 0);
        }
    }
  mt_gotoXY (x, y + 8);
  mt_setfgcolor (BLUE);
  printf ("Номер редактируемой ячейки: %03d", 0);
  mt_setdefaultcolor ();
}

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
  printDecodedCommand (15);
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

  // int big[2] = { 0x818181FF, 0xFF818181 };
  // bc_printbigchar (big, 67, 9, WHITE, BLACK);

  char cell[5] = "0000"; // Пример значения ячейки
  int x = 67;            // Пример координаты x
  int y = 9;             // Пример координаты y

  // Вызов функции для вывода увеличенного значения текущей редактируемой
  // ячейки
  printBigCell2 (cell, x, y);
  mt_gotoXY (0, 25);
  return 0;
}