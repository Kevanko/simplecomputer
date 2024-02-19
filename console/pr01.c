#include "../include/mySimpleComputer.h"
#include "console.h"
#include <stdio.h>

int
main ()
{
  // Инициализация оперативной памяти, аккумулятора, счетчика команд и регистра
  // флагов
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  // Установка произвольных значений в оперативную память и вывод ее
  // содержимого (в данном примере установим все ячейки памяти в значение 5)
  for (int i = 7; i < 26; i++)
  {
    sc_memorySet (i, 5);
  }

  // Вывод содержимого оперативной памяти
  for (int i = 0; i < MEMORY_SIZE; i++)
  {
    int value;
    sc_memoryGet (i, &value); // Получаем значение текущей ячейки памяти
    printf ("%X ", value); // Выводим значение в шестнадцатеричном формате
    if ((i + 1) % 10 == 0)
    {
      printf ("\n"); // Переход на новую строку после каждых 10 ячеек
    }
  }
  printf ("\n");

  // Попытка задать недопустимое значение ячейке памяти
  int invalidMemoryValue = 200;
  int result = sc_memorySet (10, invalidMemoryValue);
  printf ("Status of setting invalid memory value: %d\n", result);

  // Установка произвольных значений флагов и вывод их содержимого
  sc_regSet (FLAG_OVERFLOW_MASK, 1);
  sc_regSet (FLAG_ZERO_MASK, 0);
  sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
  printFlags ();

  // Попытка установить некорректное значение флага
  result = sc_regSet (FLAG_ZERO_MASK, 2);
  printf ("Status of setting invalid flag value: %d\n", result);

  // Установка значения аккумулятора и вывод его на экран
  sc_accumulatorSet (100);
  int accumulatorValue;
  sc_accumulatorGet (&accumulatorValue);
  printf ("Accumulator value: %d\n", accumulatorValue);

  // Попытка задать недопустимое значение аккумулятору
  int invalidAccValue = 300;
  result = sc_accumulatorSet (invalidAccValue);
  printf ("Status of setting invalid accumulator value: %d\n", result);

  // Установка значения счетчика команд и вывод его на экран
  sc_icounterSet (50);
  int counterValue;
  sc_icounterGet (&counterValue);
  printf ("Counter value: %d\n", counterValue);

  // Попытка задать недопустимое значение счетчику команд
  int invalidCounterValue = -10;
  result = sc_icounterSet (invalidCounterValue);
  printf ("Status of setting invalid counter value: %d\n", result);

  // Декодирование значения произвольной ячейки памяти и значения аккумулятора
  int memValue;
  sc_memoryGet (0, &memValue);
  printf ("Decoded memory value: %d\n", memValue);
  printf ("Decoded accumulator value: %d\n", accumulatorValue);

  // Кодирование команды и вывод полученного значения в разных системах
  // счисления
  int command = 10; // Пример команды
  int encodedValue;
  sc_commandEncode (0, command, 0, &encodedValue);
  printf ("Encoded command value in decimal: %d\n", encodedValue);
  printf ("Encoded command value in binary: ");
  for (int i = 0; i < 32; i++)
  {
    printf ("%d", (encodedValue >> (31 - i)) & 1);
  }
  printf ("\n");

  return 0;
}
