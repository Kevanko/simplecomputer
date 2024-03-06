#include "console.h"

void
printCounters ()
{
  int x = 91;
  int y = 2;
  int icounter;
  sc_icounterGet (&icounter);
  mt_gotoXY (y, x);
  printf ("T: %02d  IC: +0000", icounter);
}