#include "../include/mySimpleComputer.h"
#include <stdio.h>

// Выводит на экран содержимое ячейки оперативной памяти по указанному адресу
void
printCell (int address)
{
  int value;
  sc_memoryGet (address, &value);
  printf("%d", value);
}

// Выводит значения флагов в заданном формате
void
printFlags ()
{
  int flags;
  if (sc_regGet (0, &flags) == 0)
    {
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
  for (int i = 14; i >= 0; i--)
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
  sc_accumulatorGet (&accumulator);
  printf ("Accumulator: %d\n", accumulator);
}

// Выводит значение счетчика команд
void
printCounters ()
{
  int icounter;
  sc_icounterGet (&icounter);
  printf ("Instruction Counter: %d\n", icounter);
}