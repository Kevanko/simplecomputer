#include "console.h"

void
printCommand (void)
{
  int cmd = memory[instruction_counter];
  int sign, commandCode, operand;

  mt_gotoXY (COMMAND_X, COMMAND_Y);

  if (sc_commandValidate (cmd))
    {
      printf ("! %02X : %02X", cmd & COMMAND_SIGN_BIT,
              (cmd >> COMMAND_COMMAND_SHIFT) & 0x7F);
    }
  else
    {
      sc_commandDecode (cmd, &sign, &commandCode, &operand);
      printf ("+%02X : %02X", commandCode, operand);
    }
}