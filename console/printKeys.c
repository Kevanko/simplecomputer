#include "console.h"

void
printKeys ()
{
  mt_gotoXY (85, 20);
  printf ("l - load s - save i - reset\n");
  mt_gotoXY (85, 21);
  printf ("r - run t - step\n");
  mt_gotoXY (85, 22);
  printf ("esc - выход\n");
  mt_gotoXY (85, 23);
  printf ("F5 - Accumulator\n");
  mt_gotoXY (85, 24);
  printf ("F6 - Instruction counter\n");
}