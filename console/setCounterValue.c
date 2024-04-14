#include "console.h"

int
setCounterValue ()
{
  mt_gotoXY (INSTR_COUNTER_X + 11, INSTR_COUNTER_Y);
  int number;
  rk_readvalue (&number, 0);
  sc_icounterSet (number);
  return 0;
}