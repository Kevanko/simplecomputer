#include <mySimpleComputer.h>

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (value & ~0x7FFF)
    return -1; // биты, не соответствующие формату команды
  *sign = (value & COMMAND_SIGN_BIT) ? 1 : 0;
  *command = (value & COMMAND_COMMAND_BITS) >> COMMAND_COMMAND_SHIFT;
  *operand = value & COMMAND_OPERAND_BITS;
  return 0;
}