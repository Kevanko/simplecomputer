#include <mySimpleComputer.h>

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