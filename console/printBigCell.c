#include "console.h"

void
printBigCell (int cell, int x, int y)
{
  bc_printbigchar (font[16], x, y, 0, 0);

  for (int i = 0; i < 4; ++i)
    {
      int cell_id = (cell >> sizeof (int) * (3 - i)) & 0xF;
      bc_printbigchar (font[cell_id], x + (i + 1) * 9, y, 0, 0);
    }
  mt_gotoXY (x, y + 8);
  mt_setfgcolor (BLUE);
  printf ("Номер редактируемой ячейки: %03d", ACTIVE_MEMORY);
  mt_setdefaultcolor ();
}