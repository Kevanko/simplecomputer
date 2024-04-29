#include "console.h"

void
printCommand (void)
{
  int sign, command, operand;
  sc_commandDecode (memory[instruction_counter], &sign, &command, &operand);
  mt_gotoXY (COMMAND_X, COMMAND_Y);

  if (sc_commandValidate (command) || sign)
    {
      printf ("! %02X : %02X  ", command, command);
    }
  else
    {
      printf ("+%02X : %02d  ", command, operand);
    }
}