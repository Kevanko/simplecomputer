#include "console.h"

void
drawConsole ()
{
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
}