#include "../include/mySimpleComputer.h"
#include <stdio.h>

// Выводит на экран содержимое ячейки оперативной памяти по указанному адресу
void
printCell (int address)
{
  int value;
  // Получаем значение ячейки памяти по указанному адресу
  sc_memoryGet (address, &value);
  // Выводим значение ячейки в декодированном виде
  printf ("%04X: %04X\n", address, value);
}

// Выводит значения флагов в заданном формате
void
printFlags ()
{
  int flags;
  // Получаем значения всех флагов
  if (sc_regGet (0, &flags) == 0)
  {
    // Выводим значения флагов в заданном формате
    printf ("Flags: %c%c%c\n", (flags & FLAG_OVERFLOW_MASK) ? 'O' : '_',
            (flags & FLAG_ZERO_MASK) ? 'Z' : '_',
            (flags & FLAG_OUT_OF_MEMORY_MASK) ? 'M' : '_');
  }
}

// Выводит переданное значение в различных системах счисления
void
printDecodedCommand (int value)
{
  printf ("Decimal: %d\n", value);
  printf ("Octal: %o\n", value);
  printf ("Hexadecimal: %X\n", value);
  printf ("Binary: ");
  for (int i = 15; i >= 0; i--)
  {
    printf ("%d", (value >> i) & 1);
  }
  printf ("\n");
}

// Выводит значение аккумулятора
void
printAccumulator ()
{
  int accumulator;
  // Получаем значение аккумулятора
  sc_accumulatorGet (&accumulator);
  // Выводим значение аккумулятора
  printf ("Accumulator: %04X\n", accumulator);
}

// Выводит значение счетчика команд
void
printCounters ()
{
  int icounter;
  // Получаем значение счетчика команд
  sc_icounterGet (&icounter);
  // Выводим значение счетчика команд
  printf ("Instruction Counter: %04X\n", icounter);
}