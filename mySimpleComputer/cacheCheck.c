#include <mySimpleComputer.h>

int
cacheCheck (int instruction)
{
  CACHE *tmp = &cache[0];
  for (int i = 0; i < CACHE_LINES; i++)
    {
      if (cache[i].c_uses < tmp->c_uses)
        {
          tmp = &cache[i];
        }
      for (int j = 0; j < CACHE_LINE_SIZE; j++)
        {
          if (cache[i].c_line[j] == instruction)
            {
              cache[i].c_uses += 1;
              return 0;
            }
        }
    }
  mt_gotoXY (0, 26);
  printf ("cacheload [%d]", instruction_counter / 10);
  cacheLoad (tmp);
  return 1;
}