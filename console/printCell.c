#include "console.h"
#include <mySimpleComputer.h>
#include <stdio.h>

#define CELL_WIDTH 6
#define CELL_HEIGHT 1

void
printCell (int address, enum colors fg, enum colors bg)
{
  // x и y - это координаты начала блока "Оперативная память"
  int x = 1;
  int y = 2;

  int cell_x = x + (address % 10) * CELL_WIDTH + 1;
  int cell_y = y + (address / 10) * CELL_HEIGHT;

  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  mt_gotoXY (cell_y, cell_x);

  int value = memory[address];
  printf ("+%04X", value);

  mt_setdefaultcolor ();
}
