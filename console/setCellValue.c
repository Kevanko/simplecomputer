#include "console.h"

int
setCellValue ()
{
  mt_gotoXY (ACTIVE_MEMORY % 10 * 6 + MEMORY_X + 1,
             ACTIVE_MEMORY / 10 + MEMORY_Y);
  int number;
  rk_readvalue (&number, 0);
  sc_memorySet (ACTIVE_MEMORY, number);
  return 0;
}