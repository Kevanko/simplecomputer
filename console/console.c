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
  //                 0=======-------
  sc_memorySet (0, 0b001000000001010);
  // загружаем ячейку 10 в аккумулятор
  sc_memorySet (1, 0b001100000001011);
  // складываем значение аккумулятора с 11 ячейкой
  sc_memorySet (2, 0b001100010001100);
  // вычитаем из аккумулятора с 12 ячейку
  sc_memorySet (3, 0b001000010001101);
  // выгружаем из аккумулятора значение в 13 ячейку
  sc_memorySet (4, 0b011000000001101);
  // логический двоичный сдвиг влево ячейки 13 [CHL]
  sc_memorySet (5, 0b001000010001110);
  // выгружаем из аккумулятора значение в 14 ячейку
  sc_memorySet (6, 0b010101010001101);
  // переход на 14 ячейку если в аккумуляторе
  // положительное число [JNS]

  sc_memorySet (10, 2);
  sc_memorySet (11, 2);
  sc_memorySet (12, 6);

  // ожидаемый результат 13 ячейки: 25 + 125 - 50 = 100 (0x64)
  // ожидаемый результат 14 ячейки: 100 << 2 = 200 (0xC8)

  sc_regSet (FLAG_OVERFLOW_MASK, 0);
  sc_regSet (FLAG_DIVISION_BY_ZERO_MASK, 0);
  sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 0);
  sc_regSet (FLAG_INVALID_COMMAND_MASK, 0);
  sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);

  signal (SIGALRM, IRC);
  signal (SIGUSR1, IRC);

  rk_mytermsave ();
  enum keys key;
  while (key != KEY_ESC)
    {
      drawConsole ();
      rk_readkey (&key);
      handleKeypress (&key);
      alarm (1);
      sleep (0.01);
    }
  return 0;
}