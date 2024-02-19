#include "../include/mySimpleComputer.h"
#include <stdio.h>
#include <stdlib.h>

// Глобальные переменные для регистров
static int accumulator;
static int instruction_counter;
static int flags_register;
// Глобальная переменная для памяти
static int memory[MEMORY_SIZE];

int
sc_memoryInit (void)
{
  for (int i = 0; i < MEMORY_SIZE; i++)
  {
    memory[i] = 0;
  }
  return 0;
}

int
sc_memorySet (int address, int value)
{
  if (address < 0 || address >= MEMORY_SIZE || value < 0 || value > 0x7FFF)
  {
    return -1; // выход за границы или недопустимое значение
  }
  memory[address] = value;
  return 0;
}

int
sc_memoryGet (int address, int *value)
{
  if (address < 0 || address >= MEMORY_SIZE || !value)
  {
    return -1; // выход за границы или неверный указатель
  }
  *value = memory[address];
  return 0;
}

int
sc_memorySave (char *filename)
{
  if (!filename)
  {
    return -1; // неверный указатель на имя файла
  }
  FILE *file = fopen (filename, "wb");
  if (!file)
  {
    return -1; // ошибка открытия файла
  }
  fwrite (memory, sizeof (int), MEMORY_SIZE, file);
  fclose (file);
  return 0;
}

int
sc_memoryLoad (char *filename)
{
  if (!filename)
  {
    return -1; // неверный указатель на имя файла
  }
  FILE *file = fopen (filename, "rb");
  if (!file)
  {
    return -1; // ошибка открытия файла
  }
  int buffer[MEMORY_SIZE];
  fread (buffer, sizeof (int), MEMORY_SIZE, file);
  fclose (file);
  // Если чтение успешно, переносим содержимое в оперативную память
  for (int i = 0; i < MEMORY_SIZE; i++)
  {
    memory[i] = buffer[i];
  }
  return 0;
}

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