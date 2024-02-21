#include <mySimpleComputer.h>

extern int memory;

int
sc_memoryInit (void)
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      memory[i] = 0;
    }
  return 0;
}