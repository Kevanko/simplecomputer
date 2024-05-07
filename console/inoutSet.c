#include "console.h"

void
inoutSet (int operand, int value)
{
  INOUT_ARRAY[0] = operand;
  INOUT_INPUT[0] = value;
}