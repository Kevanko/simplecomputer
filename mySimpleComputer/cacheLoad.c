#include <mySimpleComputer.h>

void
cacheLoad (CACHE *changed)
{
  changed->c_number = instruction_counter / 10;
  changed->c_uses = 0;
  for (int i = 0; i < CACHE_LINE_SIZE; i++)
    {
      changed->c_line[i] = memory[(instruction_counter / 10) * 10 + i];
    }
}