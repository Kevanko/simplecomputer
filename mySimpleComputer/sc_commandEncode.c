#include "../include/mySimpleComputer.h"

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (sign != 0 && sign != 1)
    return -1;
  if (command < 0 || command > 127)
    return -1;
  if (operand < 0 || operand > 63)
    return -1;

  *value = (sign << 15) | (command << 10) | operand;
  return 0;
}