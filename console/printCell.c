#include "console.h"
#include <mySimpleComputer.h>
#include <stdio.h>

#define CELL_WIDTH 6
#define CELL_HEIGHT 1

void
printCell (int address, enum colors fg, enum colors bg)
{
  int x = (address % 10) * 6 + 1 + MEMORY_X;
  int y = (address / 10) + MEMORY_Y;
  mt_setfgcolor (fg);
  if (bg != 0)
    mt_setbgcolor (bg);
  mt_gotoXY (x, y);
  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (memory[address], &sign, &command, &operand);
  if (sign)
    printf ("-");
  else
    printf ("+");
  printf ("%04X", memory[address] & ~COMMAND_SIGN_BIT);
  mt_setdefaultcolor ();
  printf (" ");
}
