#include "console.h"

int
setCellValue ()
{
  mt_gotoXY (instruction_counter % 10 * 6 + MEMORY_X + 1,
             instruction_counter / 10 + MEMORY_Y);
  int number;
  rk_readvalue (&number, 0);
  sc_memorySet (instruction_counter, number);
  return 0;
}