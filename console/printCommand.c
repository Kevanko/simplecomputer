#include "console.h"

void
printCommand ()
{
  int cmd = memory[instruction_counter];
  mt_gotoXY (COMMAND_X, COMMAND_Y);
  if (!sc_commandValidate (cmd))
    {
      printf ("! %02d : %02X", cmd >> 7, cmd);
    }
  else
    {
      int sign, command, operand;
      sc_commandDecode (cmd, &sign, &command, &operand);
      printf ("  %02d : %02X", sign << 14 | command << 7 | operand, command);
    }
}