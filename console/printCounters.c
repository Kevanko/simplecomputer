#include "console.h"

void
printCounters ()
{
  int icounter;
  sc_icounterGet (&icounter);
  mt_gotoXY (INSTR_COUNTER_X, INSTR_COUNTER_Y);
  printf ("T: %02d  IC: +%04x", 0, icounter);
}