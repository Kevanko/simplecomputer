#include <mySimpleComputer.h>

int
sc_memoryInit (void)
{
  memory = calloc (MEMORY_SIZE, sizeof (int));
  return 0;
}