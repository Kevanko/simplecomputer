#include <mySimpleComputer.h>

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
